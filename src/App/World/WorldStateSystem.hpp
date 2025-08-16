#pragma once

#include "App/Quest/QuestPhaseExecutor.hpp"
#include "App/Quest/QuestPhaseRegistry.hpp"

namespace App
{
class WorldStateSystem : public Red::IGameSystem
{
public:
    bool IsReady();

    Red::Handle<Red::worldStreamingWorld> GetStreamingWorld();

    void ActivateCommunity(Red::NodeRef aNodeRef, Red::Optional<Red::CName> aEntryName);
    void DeactivateCommunity(Red::NodeRef aNodeRef, Red::Optional<Red::CName> aEntryName);

    void ToggleNode(Red::NodeRef aNodeRef, bool aState);
    void ToggleVariant(Red::NodeRef aNodeRef, Red::CName aVariant, bool aState);

private:
    void OnWorldAttached(Red::world::RuntimeScene*) override;
    void OnAfterWorldDetach() override;

    bool m_ready;

    Core::SharedPtr<QuestPhaseRegistry> m_questPhaseRegistry;
    Core::UniquePtr<QuestPhaseExecutor> m_questPhaseExecutor;

    Red::gameICommunitySystem* m_communitySystem;
    Red::questIQuestsSystem* m_questsSystem;
    Red::FactManager* m_factManager;

    RTTI_IMPL_TYPEINFO(App::WorldStateSystem);
    RTTI_IMPL_ALLOCATOR();
};
}

RTTI_DEFINE_CLASS(App::WorldStateSystem, {
    RTTI_METHOD(IsReady);
    RTTI_METHOD(GetStreamingWorld);
    RTTI_METHOD(ActivateCommunity);
    RTTI_METHOD(DeactivateCommunity);
    RTTI_METHOD(ToggleNode);
    RTTI_METHOD(ToggleVariant);
});
