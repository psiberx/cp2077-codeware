#include "WidgetSpawningService.hpp"
#include "App/Callback/CallbackSystem.hpp"
#include "App/Callback/Events/InkWidgetSpawnEvent.hpp"

namespace
{
constexpr auto ControllerSeparator = ':';

Red::ClassLocator<Red::inkIWidgetController> s_gameControllerType;
Red::ClassLocator<Red::inkWidgetLogicController> s_logicControllerType;
}

void App::WidgetSpawningService::OnBootstrap()
{
    Hook<Raw::InkWidgetLibrary::SpawnFromLocal>(&OnSpawnLocal).OrThrow();
    Hook<Raw::InkWidgetLibrary::SpawnFromExternal>(&OnSpawnExternal).OrThrow();
    Hook<Raw::InkWidgetLibrary::AsyncSpawnFromLocal>(&OnAsyncSpawnLocal).OrThrow();
    Hook<Raw::InkWidgetLibrary::AsyncSpawnFromExternal>(&OnAsyncSpawnExternal).OrThrow();
    Hook<Raw::InkWidgetLibrary::FindExternalLibrary>(&OnFindExternalLibrary).OrThrow();
    HookBefore<Raw::InkSpawner::FinishAsyncSpawn>(&OnFinishAsyncSpawn).OrThrow();
}

void App::WidgetSpawningService::OnShutdown()
{
    Unhook<Raw::InkWidgetLibrary::SpawnFromLocal>();
    Unhook<Raw::InkWidgetLibrary::SpawnFromExternal>();
    Unhook<Raw::InkWidgetLibrary::AsyncSpawnFromLocal>();
    Unhook<Raw::InkWidgetLibrary::AsyncSpawnFromExternal>();
    Unhook<Raw::InkWidgetLibrary::FindExternalLibrary>();
    Unhook<Raw::InkSpawner::FinishAsyncSpawn>();
}

void* App::WidgetSpawningService::OnSpawnLocal(Red::inkWidgetLibraryResource* aLibrary,
                                               Red::Handle<Red::inkWidgetLibraryItemInstance>& aOut,
                                               Red::CName aItemName)
{
    auto result = Raw::InkWidgetLibrary::SpawnFromLocal(aLibrary, aOut, aItemName);

    if (!aOut)
    {
        auto* itemNameStr = aItemName.ToString();
        auto* controllerSep = strchr(itemNameStr, ControllerSeparator);

        if (controllerSep)
        {
            aItemName = Red::CName(itemNameStr, controllerSep - itemNameStr);
            Raw::InkWidgetLibrary::SpawnFromLocal(aLibrary, aOut, aItemName);

            if (aOut)
            {
                InjectController(aOut, controllerSep + 1);
            }
        }
    }

    if (s_widgetSpawnEventEnabled && aOut)
    {
        CallbackSystem::Get()->DispatchNativeEvent<inkWidgetSpawnEvent>(WidgetSpawnEventName, aLibrary->path, aItemName,
                                                                        aOut);
    }

    return result;
}

void* App::WidgetSpawningService::OnSpawnExternal(Red::inkWidgetLibraryResource* aLibrary,
                                                  Red::Handle<Red::inkWidgetLibraryItemInstance>& aOut,
                                                  Red::ResourcePath aExternalPath, Red::CName aItemName)
{
    if (aExternalPath && aLibrary->path != aExternalPath)
    {
        if (auto externalLibrary = ResolveDependency(aLibrary, aExternalPath))
        {
            return OnSpawnLocal(externalLibrary, aOut, aItemName);
        }
    }

    aOut.instance = nullptr;
    aOut.refCount = nullptr;

    return &aOut;
}

bool App::WidgetSpawningService::OnAsyncSpawnLocal(Red::inkWidgetLibraryResource* aLibrary,
                                                   Red::InkSpawningInfo& aSpawningInfo, Red::CName aItemName,
                                                   bool aFlag)
{
    auto* itemNameStr = aItemName.ToString();
    auto* controllerSep = strchr(itemNameStr, ControllerSeparator);

    if (controllerSep)
    {
        aItemName = Red::CName(itemNameStr, controllerSep - itemNameStr);
    }

    return Raw::InkWidgetLibrary::AsyncSpawnFromLocal(aLibrary, aSpawningInfo, aItemName, aFlag);
}

bool App::WidgetSpawningService::OnAsyncSpawnExternal(Red::inkWidgetLibraryResource* aLibrary,
                                                      Red::InkSpawningInfo& aSpawningInfo,
                                                      Red::ResourcePath aExternalPath,
                                                      Red::CName aItemName,
                                                      bool aFlag)
{
    if (aExternalPath && aLibrary->path != aExternalPath)
    {
        if (auto externalLibrary = ResolveDependency(aLibrary, aExternalPath))
        {
            return OnAsyncSpawnLocal(externalLibrary, aSpawningInfo, aItemName, aFlag);
        }
    }

    return false;
}

void* App::WidgetSpawningService::OnFindExternalLibrary(Red::inkWidgetLibraryResource* aLibrary,
                                                        Red::Handle<Red::inkWidgetLibraryResource>& aOut,
                                                        Red::ResourcePath aExternalPath)
{
    std::shared_lock _(s_externalLibraryLock);

    return Raw::InkWidgetLibrary::FindExternalLibrary(aLibrary, aOut, aExternalPath);
}

void App::WidgetSpawningService::OnFinishAsyncSpawn(Red::InkSpawningContext& aContext,
                                                    Red::Handle<Red::inkWidgetLibraryItemInstance>& aInstance)
{
    const char* itemNameStr = nullptr;
    const char* controllerSep = nullptr;

    {
        itemNameStr = aContext.request->itemName.ToString();
        controllerSep = strchr(itemNameStr, ControllerSeparator);

        if (controllerSep)
        {
            InjectController(aInstance, controllerSep + 1);
        }
    }

    if (s_widgetSpawnEventEnabled)
    {
        auto libraryPath = aContext.request->externalLibrary
                               ? aContext.request->externalLibrary
                               : aContext.request->library->path;
        auto itemName = controllerSep
                            ? Red::CName(itemNameStr, controllerSep - itemNameStr)
                            : aContext.request->itemName;

        CallbackSystem::Get()->DispatchNativeEvent<inkWidgetSpawnEvent>(WidgetSpawnEventName, libraryPath, itemName,
                                                                        aInstance);
    }
}

Red::Handle<Red::inkWidgetLibraryResource> App::WidgetSpawningService::ResolveDependency(
    Red::inkWidgetLibraryResource* aLibrary, Red::ResourcePath aExternalPath)
{
    {
        std::shared_lock _(s_externalLibraryLock);

        for (const auto& externalLibrary : aLibrary->externalLibraries)
        {
            if (externalLibrary.path == aExternalPath)
            {
                return externalLibrary.token->resource;
            }
        }
    }

    auto token = Red::FetchResourceToken<Red::inkWidgetLibraryResource>(aExternalPath, std::chrono::milliseconds(1000));

    {
        std::unique_lock _(s_externalLibraryLock);

        aLibrary->externalLibraries.EmplaceBack(aExternalPath);
    }

    return token->resource;
}

void App::WidgetSpawningService::InjectController(Red::Handle<Red::inkWidgetLibraryItemInstance>& aOut,
                                                  Red::CName aControllerName)
{
    auto* controllerType = Red::CRTTISystem::Get()->GetClass(aControllerName);

    if (controllerType)
    {
        if (controllerType->IsA(s_gameControllerType))
        {
            auto* controllerInstance = reinterpret_cast<Red::inkIWidgetController*>(controllerType->CreateInstance(true));
            Red::Handle<Red::inkIWidgetController> controllerHandle(controllerInstance);

            aOut->gameController.Swap(controllerHandle);

            if (controllerHandle.instance)
            {
                InheritProperties(controllerInstance, controllerHandle.instance);
            }
        }
        else if (controllerType->IsA(s_logicControllerType))
        {
            auto* controllerInstance = reinterpret_cast<Red::inkWidgetLogicController*>(controllerType->CreateInstance(true));
            Red::Handle<Red::inkWidgetLogicController> controllerHandle(controllerInstance);

            aOut->rootWidget->logicController.Swap(controllerHandle);

            if (controllerHandle.instance)
            {
                InheritProperties(controllerInstance, controllerHandle.instance);
            }
        }
    }
}

void App::WidgetSpawningService::InheritProperties(Red::IScriptable* aTarget, Red::IScriptable* aSource)
{
    auto* sourceType = aSource->GetType();
    auto* targetType = aTarget->GetType();

    Red::DynArray<Red::CProperty*> sourceProps;
    sourceType->GetProperties(sourceProps);

    for (const auto& sourceProp : sourceProps)
    {
        const auto targetProp = targetType->GetProperty(sourceProp->name);

        if (targetProp && targetProp->type == sourceProp->type)
        {
            targetProp->SetValue(aTarget, sourceProp->GetValuePtr<void>(aSource));
        }
    }
}

void App::WidgetSpawningService::ToggleWidgetSpawnEvent(bool aState)
{
    s_widgetSpawnEventEnabled = aState;
}
