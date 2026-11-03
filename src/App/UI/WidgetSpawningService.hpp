#pragma once

#include "Core/Foundation/Feature.hpp"
#include "Core/Hooking/HookingAgent.hpp"
#include "Core/Logging/LoggingAgent.hpp"
#include "Red/InkLibrary.hpp"

namespace App
{
class WidgetSpawningService
    : public Core::Feature
    , public Core::HookingAgent
    , public Core::LoggingAgent
{
public:
    static constexpr auto WidgetSpawnEventName = "InkWidget/Spawn";

    static void ToggleWidgetSpawnEvent(bool aState);

protected:
    void OnBootstrap() override;
    void OnShutdown() override;

    static uintptr_t OnSpawnLocal(Red::ink::WidgetLibraryResource& aLibrary,
                                  Red::Handle<Red::ink::WidgetLibraryItemInstance>& aInstance,
                                  Red::CName aItemName);
    static uintptr_t OnSpawnExternal(Red::ink::WidgetLibraryResource& aLibrary,
                                     Red::Handle<Red::ink::WidgetLibraryItemInstance>& aInstance,
                                     Red::ResourcePath aExternalPath,
                                     Red::CName aItemName);
#if !defined(__APPLE__)
    static bool OnAsyncSpawnLocal(Red::ink::WidgetLibraryResource& aLibrary, Red::InkSpawningInfo& aSpawningInfo,
                                  Red::CName aItemName, bool aFlag);
    static bool OnAsyncSpawnExternal(Red::ink::WidgetLibraryResource& aLibrary,
                                     Red::InkSpawningInfo& aSpawningInfo,
                                     Red::ResourcePath aExternalPath,
                                     Red::CName aItemName);
#endif
    static void OnFinishAsyncSpawn(Red::InkSpawningContext& aContext,
                                   Red::Handle<Red::ink::WidgetLibraryItemInstance>& aInstance);

#if defined(__APPLE__)
    // R20. The Mac ABI forms of the four spawn hooks (see src/Red/InkLibrary.hpp): the Handle comes back through x8, and the
    // two Async* functions carry one more bool. The Windows-shaped handlers above hold the logic.
    static Red::Handle<Red::ink::WidgetLibraryItemInstance> OnSpawnLocalMac(Red::ink::WidgetLibraryResource& aLibrary,
                                                                            Red::CName aItemName);
    static Red::Handle<Red::ink::WidgetLibraryItemInstance> OnSpawnExternalMac(Red::ink::WidgetLibraryResource& aLibrary,
                                                                               Red::ResourcePath aExternalPath,
                                                                               Red::CName aItemName);
    static bool OnAsyncSpawnLocalMac(Red::ink::WidgetLibraryResource& aLibrary,
                                     Red::InkSpawningInfo& aSpawningInfo,
                                     Red::CName aItemName,
                                     bool aFlag);
    static bool OnAsyncSpawnExternalMac(Red::ink::WidgetLibraryResource& aLibrary,
                                        Red::InkSpawningInfo& aSpawningInfo,
                                        Red::ResourcePath aExternalPath,
                                        Red::CName aItemName,
                                        bool aFlag);
    static void MacCheckSpawnedInstance(const Red::Handle<Red::ink::WidgetLibraryItemInstance>& aInstance, const char* aWhere);
#endif

    inline static void InjectDependency(Red::ink::WidgetLibraryResource& aLibrary,
                                        Red::ResourcePath aExternalPath);
    inline static void InjectController(Red::Handle<Red::ink::WidgetLibraryItemInstance>& aInstance,
                                        Red::CName aControllerName);
    inline static void InheritProperties(Red::IScriptable* aTarget, Red::IScriptable* aSource);

    inline static std::shared_mutex s_mutex;
    inline static bool s_widgetSpawnEventEnabled{false};
};
}
