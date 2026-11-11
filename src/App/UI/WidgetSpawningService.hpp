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

    static void* OnSpawnLocal(Red::inkWidgetLibraryResource* aLibrary,
                              Red::Handle<Red::inkWidgetLibraryItemInstance>& aOut, Red::CName aItemName);
    static void* OnSpawnExternal(Red::inkWidgetLibraryResource* aLibrary,
                                 Red::Handle<Red::inkWidgetLibraryItemInstance>& aOut, Red::ResourcePath aExternalPath,
                                 Red::CName aItemName);
    static bool OnAsyncSpawnLocal(Red::inkWidgetLibraryResource* aLibrary, Red::InkSpawningInfo& aSpawningInfo,
                                  Red::CName aItemName, bool aFlag);
    static bool OnAsyncSpawnExternal(Red::inkWidgetLibraryResource* aLibrary, Red::InkSpawningInfo& aSpawningInfo,
                                     Red::ResourcePath aExternalPath, Red::CName aItemName, bool aFlag);
    static void* OnFindExternalLibrary(Red::inkWidgetLibraryResource* aLibrary,
                                       Red::Handle<Red::inkWidgetLibraryResource>& aExternalLibrary,
                                       Red::ResourcePath aExternalPath);
    static void OnFinishAsyncSpawn(Red::InkSpawningContext& aContext,
                                   Red::Handle<Red::inkWidgetLibraryItemInstance>& aInstance);

    inline static Red::Handle<Red::inkWidgetLibraryResource> ResolveDependency(Red::inkWidgetLibraryResource* aLibrary,
                                                                               Red::ResourcePath aExternalPath);
    inline static void InjectController(Red::Handle<Red::inkWidgetLibraryItemInstance>& aInstance,
                                        Red::CName aControllerName);
    inline static void InheritProperties(Red::IScriptable* aTarget, Red::IScriptable* aSource);

    inline static Red::SharedSpinLock s_externalLibraryLock;
    inline static bool s_widgetSpawnEventEnabled{false};
};
}
