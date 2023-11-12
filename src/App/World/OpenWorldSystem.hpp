#pragma once

#include "App/Quest/QuestPhaseExecutor.hpp"
#include "App/Quest/QuestPhaseRegistry.hpp"

namespace App
{
enum class OpenWorldActivityResult
{
    OK,
    Invalid,
    NotFound,
    Undiscovered,
    Unfinished,
    StillSpawned,
};

struct OpenWorldActivityState
{
    OpenWorldActivityState();
    explicit OpenWorldActivityState(const Core::SharedPtr<ActivityDefinition>& aSource);

    Red::CName name;
    Red::CName kind;
    Red::gamedataDistrict district;
    Red::gamedataDistrict area;
    uint32_t timestamp;
    bool completed;
    bool discovered;
    bool valid;
};

struct OpenWorldActivityRequest
{
    OpenWorldActivityRequest();

    [[nodiscard]] bool IsDefault() const;
    [[nodiscard]] bool HasCooldown() const;
    [[nodiscard]] bool Match(const App::OpenWorldActivityState& aActivity, uint32_t aGameTime,
                             float aRealTimeMultiplier) const;

    Red::CName kind;
    Red::DynArray<Red::gamedataDistrict> districts;
    float cooldown;
    bool force;
};

class OpenWorldSystem : public Red::IGameSystem
{
public:
    bool IsReady();

    OpenWorldActivityState GetActivity(Red::CName aName);
    Red::DynArray<OpenWorldActivityState> GetActivities();

    OpenWorldActivityResult StartActivity(Red::CName aName, Red::Optional<bool> aForce);
    int32_t StartActivities(Red::Optional<OpenWorldActivityRequest>& aRequest);

    void PrintActivities(Red::Optional<OpenWorldActivityRequest>& aRequest);
    void DumpActivities();

private:
    void OnWorldAttached(Red::world::RuntimeScene*) override;
    void OnAfterWorldDetach() override;
    bool OnGameRestored() override;

    bool IsActivityCompleted(const Core::SharedPtr<ActivityDefinition>& aActivity);
    OpenWorldActivityState MakeActivityState(const Core::SharedPtr<ActivityDefinition>& aActivity);
    OpenWorldActivityResult ProcessActivity(const Core::SharedPtr<ActivityDefinition>& aActivity);

    bool m_ready;

    Core::SharedPtr<QuestPhaseRegistry> m_questPhaseRegistry;
    Core::UniquePtr<QuestPhaseExecutor> m_questPhaseExecutor;

    Red::gameICommunitySystem* m_communitySystem;
    Red::gameIPopulationSystem* m_populationSystem;
    Red::gameIPersistencySystem* m_persistencySystem;
    Red::gameIContainerManager* m_containerManager;
    Red::gameIJournalManager* m_journalManager;
    Red::gamemappinsIMappinSystem* m_mappinSystem;
    Red::questIQuestsSystem* m_questsSystem;
    Red::FactManager* m_factManager;

    RTTI_IMPL_TYPEINFO(App::OpenWorldSystem);
    RTTI_IMPL_ALLOCATOR();
};
}

RTTI_DEFINE_ENUM(App::OpenWorldActivityResult);

RTTI_DEFINE_CLASS(App::OpenWorldActivityState, {
    RTTI_PROPERTY(name);
    RTTI_PROPERTY(kind);
    RTTI_PROPERTY(district);
    RTTI_PROPERTY(timestamp);
    RTTI_PROPERTY(completed);
    RTTI_PROPERTY(discovered);
});

RTTI_DEFINE_CLASS(App::OpenWorldActivityRequest, {
    RTTI_PROPERTY(kind);
    RTTI_PROPERTY(districts);
    RTTI_PROPERTY(cooldown);
    RTTI_PROPERTY(force);
});

RTTI_DEFINE_CLASS(App::OpenWorldSystem, {
    RTTI_GETTER(m_ready);
    RTTI_METHOD(GetActivity);
    RTTI_METHOD(GetActivities);
    RTTI_METHOD(StartActivity);
    RTTI_METHOD(StartActivities);
    RTTI_METHOD(PrintActivities);
    RTTI_METHOD(DumpActivities);
});
