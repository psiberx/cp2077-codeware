#include "WidgetSpawningService.hpp"
#include "App/Callback/CallbackSystem.hpp"
#include "App/Callback/Events/InkWidgetSpawnEvent.hpp"
#if defined(__APPLE__)
#include "MacEngine.hpp"
#include "MacR20.hpp"
#include "MacDiag.hpp"
#endif

namespace
{
constexpr auto ControllerSeparator = ':';

Red::ClassLocator<Red::ink::IWidgetController> s_gameControllerType;
Red::ClassLocator<Red::ink::WidgetLogicController> s_logicControllerType;

bool IsGameControllerInjectionEnabled()
{
#if defined(__APPLE__)
    // Without a Mac address the flag resolves to null; Codeware then injects the controllers itself, as before 1.21.
    const auto* flag = Raw::InkSpawner::ControllerInjectionEnabled::Get();
    return flag && *flag;
#else
    return Raw::InkSpawner::ControllerInjectionEnabled::Ref();
#endif
}
}

void App::WidgetSpawningService::OnBootstrap()
{
#if defined(__APPLE__)
    Hook<Raw::InkWidgetLibrary::SpawnFromLocalNative>(&OnSpawnLocalMac).OrThrow();
    Hook<Raw::InkWidgetLibrary::SpawnFromExternalNative>(&OnSpawnExternalMac).OrThrow();
    Hook<Raw::InkWidgetLibrary::AsyncSpawnFromLocal>(&OnAsyncSpawnLocalMac).OrThrow();
    Hook<Raw::InkWidgetLibrary::AsyncSpawnFromExternal>(&OnAsyncSpawnExternalMac).OrThrow();
#else
    Hook<Raw::InkWidgetLibrary::SpawnFromLocal>(&OnSpawnLocal).OrThrow();
    Hook<Raw::InkWidgetLibrary::SpawnFromExternal>(&OnSpawnExternal).OrThrow();
    Hook<Raw::InkWidgetLibrary::AsyncSpawnFromLocal>(&OnAsyncSpawnLocal).OrThrow();
    Hook<Raw::InkWidgetLibrary::AsyncSpawnFromExternal>(&OnAsyncSpawnExternal).OrThrow();
#endif
    HookBefore<Raw::InkSpawner::FinishAsyncSpawn>(&OnFinishAsyncSpawn).OrThrow();
}

void App::WidgetSpawningService::OnShutdown()
{
#if defined(__APPLE__)
    Unhook<Raw::InkWidgetLibrary::SpawnFromLocalNative>();
    Unhook<Raw::InkWidgetLibrary::SpawnFromExternalNative>();
#else
    Unhook<Raw::InkWidgetLibrary::SpawnFromLocal>();
    Unhook<Raw::InkWidgetLibrary::SpawnFromExternal>();
#endif
    Unhook<Raw::InkWidgetLibrary::AsyncSpawnFromLocal>();
    Unhook<Raw::InkWidgetLibrary::AsyncSpawnFromExternal>();
    Unhook<Raw::InkSpawner::FinishAsyncSpawn>();
}

#if defined(__APPLE__)
Red::Handle<Red::ink::WidgetLibraryItemInstance> App::WidgetSpawningService::OnSpawnLocalMac(
    Red::ink::WidgetLibraryResource& aLibrary, Red::CName aItemName)
{
    static auto& counter = Mac::HookCount("InkWidgetLibrary_SpawnFromLocal");
    Mac::Hit(counter);

    Red::Handle<Red::ink::WidgetLibraryItemInstance> instance;
    OnSpawnLocal(aLibrary, instance, aItemName);

    if (instance && Mac::R20Once("spawnLocal"))
    {
        MacCheckSpawnedInstance(instance, "SpawnFromLocal");
    }
    return instance;
}

Red::Handle<Red::ink::WidgetLibraryItemInstance> App::WidgetSpawningService::OnSpawnExternalMac(
    Red::ink::WidgetLibraryResource& aLibrary, Red::ResourcePath aExternalPath, Red::CName aItemName)
{
    static auto& counter = Mac::HookCount("InkWidgetLibrary_SpawnFromExternal");
    Mac::Hit(counter);

    Red::Handle<Red::ink::WidgetLibraryItemInstance> instance;
    OnSpawnExternal(aLibrary, instance, aExternalPath, aItemName);

    // R28. "Item:Controller" names with an external library. On Windows the game's SpawnFromExternal reaches the hooked SpawnFromLocal of the
    // external library, which splits the name, injects the controller and dispatches the InkWidget/Spawn event (OnSpawnLocal). The Mac native does
    // not go through that hooked function, so the whole name finds no item and the spawn fails (Equipment-EX's wardrobe screen,
    // "Root:EquipmentEx.WardrobeScreenController", did not open) and no spawn event is dispatched. Same steps as OnSpawnLocal here: try the whole
    // name first, then the name without the controller and inject the controller; then the event.
    Red::CName eventItemName = aItemName;

    if (!instance)
    {
        const auto* itemNameStr = aItemName.ToString();
        const auto* controllerSep = itemNameStr ? strchr(itemNameStr, ControllerSeparator) : nullptr;

        if (controllerSep)
        {
            eventItemName = Red::CName(itemNameStr, controllerSep - itemNameStr);
            OnSpawnExternal(aLibrary, instance, aExternalPath, eventItemName);

            if (instance)
            {
                InjectController(instance, controllerSep + 1);
            }
        }
    }

    if (instance && s_widgetSpawnEventEnabled)
    {
        CallbackSystem::Get()->DispatchNativeEvent<inkWidgetSpawnEvent>(WidgetSpawnEventName, aExternalPath, eventItemName, instance);
    }

    if (instance && Mac::R20Once("spawnExternal"))
    {
        MacCheckSpawnedInstance(instance, "SpawnFromExternal");
    }
    return instance;
}

bool App::WidgetSpawningService::OnAsyncSpawnLocalMac(Red::ink::WidgetLibraryResource& aLibrary,
                                                      Red::InkSpawningInfo& aSpawningInfo,
                                                      Red::CName aItemName,
                                                      bool aFlag)
{
    static auto& counter = Mac::HookCount("InkWidgetLibrary_AsyncSpawnFromLocal");
    Mac::Hit(counter);

    auto* itemNameStr = aItemName.ToString();
    auto* controllerSep = strchr(itemNameStr, ControllerSeparator);

    if (controllerSep)
    {
        aItemName = Red::CName(itemNameStr, controllerSep - itemNameStr);
    }

    return Raw::InkWidgetLibrary::AsyncSpawnFromLocal(aLibrary, aSpawningInfo, aItemName, aFlag);
}

bool App::WidgetSpawningService::OnAsyncSpawnExternalMac(Red::ink::WidgetLibraryResource& aLibrary,
                                                         Red::InkSpawningInfo& aSpawningInfo,
                                                         Red::ResourcePath aExternalPath,
                                                         Red::CName aItemName,
                                                         bool aFlag)
{
    static auto& counter = Mac::HookCount("InkWidgetLibrary_AsyncSpawnFromExternal");
    Mac::Hit(counter);

    InjectDependency(aLibrary, aExternalPath);

    // R28. The same split as the local variant above: the library does not know "Item:Controller" as an item name (FinishAsyncSpawn injects the
    // controller from the request's whole name).
    auto* itemNameStr = aItemName.ToString();
    auto* controllerSep = itemNameStr ? strchr(itemNameStr, ControllerSeparator) : nullptr;

    if (controllerSep)
    {
        aItemName = Red::CName(itemNameStr, controllerSep - itemNameStr);
    }

    return Raw::InkWidgetLibrary::AsyncSpawnFromExternal(aLibrary, aSpawningInfo, aExternalPath, aItemName, aFlag);
}

// R20. One-shot read-only check of the first instance a spawn hook returns: the library item instance has a root widget and a
// game controller field laid out as the SDK says, and the root widget is an inkWidget.
void App::WidgetSpawningService::MacCheckSpawnedInstance(const Red::Handle<Red::ink::WidgetLibraryItemInstance>& aInstance,
                                                         const char* aWhere)
{
    const bool hasRoot = static_cast<bool>(aInstance->rootWidget);
    const auto* rootType = hasRoot ? aInstance->rootWidget->GetType() : nullptr;
    static auto* widgetType = Red::GetClass("inkWidget");
    const bool isWidget = rootType && widgetType && rootType->IsA(widgetType);
    MAC_DIAG( "[selftest] R20 %s: instance=%p root=%p type=%s isInkWidget=%d controller=%p\n", aWhere,
                 static_cast<void*>(aInstance.instance), hasRoot ? static_cast<void*>(aInstance->rootWidget.instance) : nullptr,
                 rootType ? rootType->name.ToString() : "-", isWidget ? 1 : 0,
                 static_cast<void*>(aInstance->gameController.instance));
    Mac::R20Check(hasRoot && isWidget, "a spawned library item instance has an inkWidget root widget");
}
#endif

uintptr_t App::WidgetSpawningService::OnSpawnLocal(Red::ink::WidgetLibraryResource& aLibrary,
                                                   Red::Handle<Red::ink::WidgetLibraryItemInstance>& aInstance,
                                                   Red::CName aItemName)
{
    auto result = Raw::InkWidgetLibrary::SpawnFromLocal(aLibrary, aInstance, aItemName);

    if (!aInstance && !IsGameControllerInjectionEnabled())
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

#if !defined(__APPLE__)
bool App::WidgetSpawningService::OnAsyncSpawnLocal(Red::ink::WidgetLibraryResource& aLibrary,
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

bool App::WidgetSpawningService::OnAsyncSpawnExternal(Red::ink::WidgetLibraryResource& aLibrary,
                                                      Red::InkSpawningInfo& aSpawningInfo,
                                                      Red::ResourcePath aExternalPath,
                                                      Red::CName aItemName)
{
    InjectDependency(aLibrary, aExternalPath);

    return Raw::InkWidgetLibrary::AsyncSpawnFromExternal(aLibrary, aSpawningInfo, aExternalPath, aItemName);
}

#endif

void App::WidgetSpawningService::OnFinishAsyncSpawn(Red::InkSpawningContext& aContext,
                                                    Red::Handle<Red::ink::WidgetLibraryItemInstance>& aInstance)
{
#if defined(__APPLE__)
    {
        static auto& counter = Mac::HookCount("InkSpawner_FinishAsyncSpawn");
        Mac::Hit(counter);
        if (Mac::R20Once("finishAsyncSpawn"))
        {
            const bool hasRequest = static_cast<bool>(aContext.request);
            const char* itemName = hasRequest ? aContext.request->itemName.ToString() : "";
            MAC_DIAG( "[selftest] R20 FinishAsyncSpawn: context=%p request=%p item=\"%s\" instance=%p\n",
                         static_cast<void*>(&aContext), hasRequest ? static_cast<void*>(aContext.request.instance) : nullptr,
                         itemName, static_cast<void*>(aInstance.instance));
            Mac::R20Check(hasRequest && itemName && itemName[0] != 0, "the async spawn context has a request with an item name");
        }
    }
#endif
    const char* itemNameStr = nullptr;
    const char* controllerSep = nullptr;

    if (!IsGameControllerInjectionEnabled())
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

namespace
{
// The external library list of a library resource. On macOS the SDK header's offset (0x58) is wrong: the game's layout puts it
// at 0x50 (clang places inkWidgetLibraryResource's first members in the tail padding of CResource; r20a, confirmed in the
// game's own lookup loops), so the list is reached through the reflected property.
inline auto* ExternalLibrariesOf(Red::ink::WidgetLibraryResource& aLibrary)
{
#if defined(__APPLE__)
    return Red::GetPropertyPtr<decltype(aLibrary.externalLibraries)>(&aLibrary, "externalLibraries");
#else
    return &aLibrary.externalLibraries;
#endif
}
}

void App::WidgetSpawningService::InjectDependency(Red::ink::WidgetLibraryResource& aLibrary,
                                                  Red::ResourcePath aExternalPath)
{
    auto* externalLibraries = ExternalLibrariesOf(aLibrary);

    if (!externalLibraries)
        return;

    bool libraryExists = false;

    // Check if the external library is in the list and do nothing if it is
    {
        std::shared_lock _(s_mutex);
        for (const auto& externalLibrary : *externalLibraries)
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
        externalLibraries->EmplaceBack(aExternalPath);

        // Load requested library for the spawner
        auto& externalLibrary = externalLibraries->Back();
        externalLibrary.LoadAsync();

        Red::WaitForResource(externalLibrary.token, std::chrono::milliseconds(1000));
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
