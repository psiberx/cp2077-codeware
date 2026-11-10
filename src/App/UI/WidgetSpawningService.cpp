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
    HookBefore<Raw::InkSpawner::FinishAsyncSpawn>(&OnFinishAsyncSpawn).OrThrow();
}

void App::WidgetSpawningService::OnShutdown()
{
    Unhook<Raw::InkWidgetLibrary::SpawnFromLocal>();
    Unhook<Raw::InkWidgetLibrary::SpawnFromExternal>();
    Unhook<Raw::InkWidgetLibrary::AsyncSpawnFromLocal>();
    Unhook<Raw::InkWidgetLibrary::AsyncSpawnFromExternal>();
    Unhook<Raw::InkSpawner::FinishAsyncSpawn>();
}

uintptr_t App::WidgetSpawningService::OnSpawnLocal(Red::inkWidgetLibraryResource* aLibrary,
                                                   Red::Handle<Red::inkWidgetLibraryItemInstance>& aInstance,
                                                   Red::CName aItemName)
{
    auto result = Raw::InkWidgetLibrary::SpawnFromLocal(aLibrary, aInstance, aItemName);

    if (!aInstance)
    {
        auto* itemNameStr = aItemName.ToString();
        auto* controllerSep = strchr(itemNameStr, ControllerSeparator);

        if (controllerSep)
        {
            aItemName = Red::CName(itemNameStr, controllerSep - itemNameStr);
            Raw::InkWidgetLibrary::SpawnFromLocal(aLibrary, aInstance, aItemName);

            if (aInstance)
            {
                InjectController(aInstance, controllerSep + 1);
            }
        }
    }

    if (s_widgetSpawnEventEnabled && aInstance)
    {
        CallbackSystem::Get()->DispatchNativeEvent<inkWidgetSpawnEvent>(WidgetSpawnEventName, aLibrary->path, aItemName,
                                                                        aInstance);
    }

    return result;
}

uintptr_t App::WidgetSpawningService::OnSpawnExternal(Red::inkWidgetLibraryResource* aLibrary,
                                                      Red::Handle<Red::inkWidgetLibraryItemInstance>& aInstance,
                                                      Red::ResourcePath aExternalPath,
                                                      Red::CName aItemName)
{
    if (!aExternalPath || aLibrary->path == aExternalPath)
    {
        return reinterpret_cast<uintptr_t>(aInstance.GetPtr());
    }

    if (auto externalLibrary = ResolveDependency(aLibrary, aExternalPath))
    {
        return OnSpawnLocal(externalLibrary, aInstance, aItemName);
    }

    return reinterpret_cast<uintptr_t>(aInstance.GetPtr());
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
    if (!aExternalPath || aLibrary->path == aExternalPath)
    {
        return false;
    }

    if (auto externalLibrary = ResolveDependency(aLibrary, aExternalPath))
    {
        return OnAsyncSpawnLocal(externalLibrary, aSpawningInfo, aItemName, aFlag);
    }

    return false;
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
    for (const auto& externalLibrary : aLibrary->externalLibraries)
    {
        if (externalLibrary.path == aExternalPath)
        {
            return externalLibrary.token->resource;
        }
    }

    return Red::FetchResource<Red::inkWidgetLibraryResource>(aExternalPath, std::chrono::milliseconds(1000));
}

void App::WidgetSpawningService::InjectController(Red::Handle<Red::inkWidgetLibraryItemInstance>& aInstance,
                                                  Red::CName aControllerName)
{
    auto* controllerType = Red::CRTTISystem::Get()->GetClass(aControllerName);

    if (controllerType)
    {
        if (controllerType->IsA(s_gameControllerType))
        {
            auto* controllerInstance = reinterpret_cast<Red::inkIWidgetController*>(controllerType->CreateInstance(true));
            Red::Handle<Red::inkIWidgetController> controllerHandle(controllerInstance);

            aInstance->gameController.Swap(controllerHandle);

            if (controllerHandle.instance)
            {
                InheritProperties(controllerInstance, controllerHandle.instance);
            }
        }
        else if (controllerType->IsA(s_logicControllerType))
        {
            auto* controllerInstance = reinterpret_cast<Red::inkWidgetLogicController*>(controllerType->CreateInstance(true));
            Red::Handle<Red::inkWidgetLogicController> controllerHandle(controllerInstance);

            aInstance->rootWidget->logicController.Swap(controllerHandle);

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
