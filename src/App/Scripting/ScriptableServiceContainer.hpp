#pragma once

#if defined(__APPLE__)
#include <atomic>
#endif

#include "Core/Logging/LoggingAgent.hpp"
#include "App/Scripting/ScriptableService.hpp"

namespace App
{
struct ScriptableServiceContainerState : Red::IScriptable
{
    Red::DynArray<Red::Handle<ScriptableService>> services;

    RTTI_IMPL_TYPEINFO(App::ScriptableServiceContainerState);
    RTTI_IMPL_ALLOCATOR();
};

struct ScriptableServiceContainer : Red::IGameSystem, Core::LoggingAgent
{
public:
    ScriptableServiceContainer() = default;
    ScriptableServiceContainer(const std::filesystem::path& aStateDir);

    void OnInitializeScripts();
    void OnInitializeGameInstance();

#if defined(__APPLE__)
    // R18. Runs OnInitializeGameInstance once, from the CGameFramework::InitializeGameInstance hook (aVia names the
    // path that ran it; the first world attach is the fallback).
    void MacInitializeGameInstance(const char* aVia);
#endif

    Red::Handle<ScriptableService> GetService(Red::CName aName);

    static Red::Handle<ScriptableServiceContainer>& Build(const std::filesystem::path& aStateDir);
    static Red::Handle<ScriptableServiceContainer>& Get();

private:
#if defined(__APPLE__)
    // R18. OnInitializeGameInstance runs from the CGameFramework::InitializeGameInstance hook (ScriptingService). The
    // first world attach is only the fallback when that hook was refused, and carries the R16b/R18 self-tests.
    void OnWorldAttached(Red::world::RuntimeScene* aScene) override;
    std::atomic<bool> m_gameInstanceInitialized{false};
    void MacPersistenceSelfTest(); // SELFTEST R19
#endif
    void OnBeforeWorldDetach(Red::world::RuntimeScene* aScene) override;
    uint32_t OnBeforeGameSave(const Red::JobGroup& aJobGroup, void* a2) override;
    void OnUninitialize() override;

    void LoadState();
    void SaveState();
#if defined(__APPLE__)
    void SaveStateTo(const std::filesystem::path& aPath); // R19: SaveState with a path (the self-test uses its own file)
#endif

    Core::Map<Red::CName, Red::Handle<ScriptableService>> m_services;
    std::filesystem::path m_stateFilePath;
    bool m_scriptsLoaded{false};

    inline static Red::Handle<ScriptableServiceContainer> s_self;

    RTTI_IMPL_TYPEINFO(App::ScriptableServiceContainer);
    RTTI_IMPL_ALLOCATOR();
};
}

RTTI_DEFINE_CLASS(App::ScriptableServiceContainerState, {
    RTTI_PERSISTENT(services);
});

RTTI_DEFINE_CLASS(App::ScriptableServiceContainer, {
    RTTI_METHOD(GetService);
});
