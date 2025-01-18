#include "WidgetSpawningService.hpp"
#include "App/Callback/CallbackSystem.hpp"
#include "App/Callback/Events/InkWidgetSpawnEvent.hpp"

namespace
{
constexpr auto ControllerSeparator = ':';

Red::ClassLocator<Red::ink::IWidgetController> s_gameControllerType;
Red::ClassLocator<Red::ink::WidgetLogicController> s_logicControllerType;
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

uintptr_t App::WidgetSpawningService::OnSpawnLocal(Red::ink::WidgetLibraryResource& aLibrary,
                                                   Red::Handle<Red::ink::WidgetLibraryItemInstance>& aInstance,
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
        CallbackSystem::Get()->DispatchNativeEvent<inkWidgetSpawnEvent>(WidgetSpawnEventName, aLibrary.path, aItemName,
                                                                        aInstance);
    }

    return result;
}

uintptr_t App::WidgetSpawningService::OnSpawnExternal(Red::ink::WidgetLibraryResource& aLibrary,
                                                      Red::Handle<Red::ink::WidgetLibraryItemInstance>& aInstance,
                                                      Red::ResourcePath aExternalPath,
                                                      Red::CName aItemName)
{
    InjectDependency(aLibrary, aExternalPath);

    return Raw::InkWidgetLibrary::SpawnFromExternal(aLibrary, aInstance, aExternalPath, aItemName);
}

bool App::WidgetSpawningService::OnAsyncSpawnLocal(Red::ink::WidgetLibraryResource& aLibrary,
                                                   Red::InkSpawningInfo& aSpawningInfo,
                                                   Red::CName aItemName)
{
    auto* itemNameStr = aItemName.ToString();
    auto* controllerSep = strchr(itemNameStr, ControllerSeparator);

    if (controllerSep)
    {
        aItemName = Red::CName(itemNameStr, controllerSep - itemNameStr);
    }

    return Raw::InkWidgetLibrary::AsyncSpawnFromLocal(aLibrary, aSpawningInfo, aItemName);
}

bool App::WidgetSpawningService::OnAsyncSpawnExternal(Red::ink::WidgetLibraryResource& aLibrary,
                                                      Red::InkSpawningInfo& aSpawningInfo,
                                                      Red::ResourcePath aExternalPath,
                                                      Red::CName aItemName)
{
    InjectDependency(aLibrary, aExternalPath);

    return Raw::InkWidgetLibrary::AsyncSpawnFromExternal(aLibrary, aSpawningInfo, aExternalPath, aItemName);
}

void App::WidgetSpawningService::OnFinishAsyncSpawn(Red::InkSpawningContext& aContext,
                                                    Red::Handle<Red::ink::WidgetLibraryItemInstance>& aInstance)
{
    auto* itemNameStr = aContext.request->itemName.ToString();
    auto* controllerSep = strchr(itemNameStr, ControllerSeparator);

    if (controllerSep)
    {
        InjectController(aInstance, controllerSep + 1);
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

void App::WidgetSpawningService::InjectDependency(Red::ink::WidgetLibraryResource& aLibrary, Red::ResourcePath aExternalPath)
{
    bool libraryExists = false;

    // Check if the external library is in the list and do nothing if it is
    {
        std::shared_lock _(s_mutex);
        for (const auto& externalLibrary : aLibrary.externalLibraries)
        {
            if (externalLibrary.path == aExternalPath)
            {
                libraryExists = true;
                break;
            }
        }
    }

    // Add the requested library to the list
    if (!libraryExists)
    {
        std::unique_lock _(s_mutex);
        aLibrary.externalLibraries.EmplaceBack(aExternalPath);

        // Load requested library for the spawner
        auto* externalLibrary = aLibrary.externalLibraries.End() - 1;
        externalLibrary->LoadAsync();

        Red::WaitForResource(externalLibrary->token, std::chrono::milliseconds(1000));
    }
}

void App::WidgetSpawningService::InjectController(Red::Handle<Red::ink::WidgetLibraryItemInstance>& aInstance,
                                                Red::CName aControllerName)
{
    auto* controllerType = Red::CRTTISystem::Get()->GetClass(aControllerName);

    if (controllerType)
    {
        if (controllerType->IsA(s_gameControllerType))
        {
            auto* controllerInstance = reinterpret_cast<Red::ink::IWidgetController*>(controllerType->CreateInstance(true));
            Red::Handle<Red::ink::IWidgetController> controllerHandle(controllerInstance);

            aInstance->gameController.Swap(controllerHandle);

            if (controllerHandle.instance)
            {
                InheritProperties(controllerInstance, controllerHandle.instance);
            }
        }
        else if (controllerType->IsA(s_logicControllerType))
        {
            auto* controllerInstance = reinterpret_cast<Red::ink::WidgetLogicController*>(controllerType->CreateInstance(true));
            Red::Handle<Red::ink::WidgetLogicController> controllerHandle(controllerInstance);

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
