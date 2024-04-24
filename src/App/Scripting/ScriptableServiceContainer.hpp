#pragma once

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

    Red::Handle<ScriptableService> GetService(Red::CName aName);

    static Red::Handle<ScriptableServiceContainer>& Build(const std::filesystem::path& aStateDir);
    static Red::Handle<ScriptableServiceContainer>& Get();

private:
    void OnBeforeWorldDetach(Red::world::RuntimeScene* aScene) override;
    uint32_t OnBeforeGameSave(const Red::JobGroup& aJobGroup, void* a2) override;
    void OnUninitialize() override;

    void LoadState();
    void SaveState();

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
