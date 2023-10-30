#pragma once

#include "App/World/OpenWorldRegistry.hpp"

namespace App
{
class OpenWorldSystem : public Red::IGameSystem
{
public:
    bool CanReactivateMinorActivity(Red::CName aName);
    bool ReactivateMinorActivity(Red::CName aName);
    bool ReactivateAllMinorActivities();

private:
    void OnWorldAttached(Red::world::RuntimeScene*) override;
    void OnAfterWorldDetach() override;

    bool IsMinorActivityCompleted(const Core::SharedPtr<MinorActivityData>& aActivity);
    bool ProcessMinorActivityReactivation(const Core::SharedPtr<MinorActivityData>& aActivity);

    static Red::EntityID ResolveNodeRef(Red::NodeRef aNodeRef);

    bool m_ready;

    Core::SharedPtr<OpenWorldRegistry> m_registry;

    Red::gameICommunitySystem* m_communitySystem;
    Red::gameIPopulationSystem* m_populationSystem;
    Red::gameIPersistencySystem* m_persistencySystem;
    Red::gameIJournalManager* m_journalManager;
    Red::gamemappinsIMappinSystem* m_mappinSystem;
    Red::questIQuestsSystem* m_questsSystem;
    Red::FactManager* m_factManager;

    RTTI_IMPL_TYPEINFO(App::OpenWorldSystem);
    RTTI_IMPL_ALLOCATOR();
};
}

RTTI_DEFINE_CLASS(App::OpenWorldSystem, {
    RTTI_GETTER(m_ready);

    RTTI_METHOD(CanReactivateMinorActivity);
    RTTI_METHOD(ReactivateMinorActivity);
    RTTI_METHOD(ReactivateAllMinorActivities);
});
