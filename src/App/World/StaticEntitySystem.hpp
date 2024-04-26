#pragma once

#include "App/World/StaticEntitySpec.hpp"
#include "Red/EntitySpawner.hpp"

namespace App
{
class StaticEntitySystem : public Red::IGameSystem
{
public:
    StaticEntitySystem() = default;

    [[nodiscard]] bool IsReady() const;

    Red::EntityID SpawnEntity(const StaticEntitySpecPtr& aEntitySpec);
    bool DespawnEntity(Red::EntityID aEntityID);
    bool AttachEntity(Red::EntityID aEntityID);
    bool DetachEntity(Red::EntityID aEntityID);

    bool IsManaged(Red::EntityID aEntityID);
    bool IsTagged(Red::EntityID aEntityID, Red::CName aTag);
    bool IsSpawned(Red::EntityID aEntityID);
    bool IsSpawning(Red::EntityID aEntityID);
    Red::Handle<Red::Entity> GetEntity(Red::EntityID aEntityID);
    Red::DynArray<Red::CName> GetTags(Red::EntityID aEntityID);
    bool AssignTag(Red::EntityID aEntityID, Red::CName aTag);
    bool UnassignTag(Red::EntityID aEntityID, Red::CName aTag);

    bool IsPopulated(Red::CName aTag);
    Red::EntityID GetTaggedID(Red::CName aTag);
    Red::DynArray<Red::EntityID> GetTaggedIDs(Red::CName aTag);
    Red::DynArray<Red::Handle<Red::Entity>> GetTagged(Red::CName aTag);
    void DespawnTagged(Red::CName aTag);
    void AttachTagged(Red::CName aTag);
    void DetachTagged(Red::CName aTag);

protected:
    void OnWorldAttached(Red::world::RuntimeScene*) override;
    void OnBeforeWorldDetach(Red::world::RuntimeScene* aScene) override;
    void OnAfterWorldDetach() override;
    void OnRegisterUpdates(Red::UpdateRegistrar* aRegistrar);
    void OnUpdateTick(Red::FrameInfo& aFrame, Red::JobQueue& aJobQueue);

    bool ValidateEntitySpec(const StaticEntitySpecPtr& aEntitySpec);

    bool m_ready;

    std::shared_mutex m_tokensLock;
    Core::Map<Red::EntityID, Red::SharedPtr<Red::EntitySpawnerToken>> m_tokens;

    std::shared_mutex m_entitiesLock;
    Core::Map<Red::EntityID, Red::Handle<Red::Entity>> m_entities;

    std::shared_mutex m_tagsLock;
    Core::Map<Red::EntityID, Core::Set<Red::CName>> m_tagsByEntityID;
    Core::Map<Red::CName, Core::Set<Red::EntityID>> m_entityIDsByTag;

    std::shared_mutex m_disposedLock;
    Core::Map<Red::EntityID, Red::Handle<Red::Entity>> m_disposed;

    Red::IDynamicEntityIDSystem* m_entityIDSystem;
    Red::worldRuntimeSystemEntity* m_entityRuntimeSystem;
    Red::EntitySpawner* m_entitySpawner;
    Red::worldRuntimeEntityRegistry* m_entityRegistry;

    RTTI_IMPL_TYPEINFO(App::StaticEntitySystem);
    RTTI_IMPL_ALLOCATOR();
};
}

RTTI_DEFINE_CLASS(App::StaticEntitySystem, {
    RTTI_GETTER(m_ready);

    RTTI_METHOD(SpawnEntity);
    RTTI_METHOD(DespawnEntity);
    RTTI_METHOD(AttachEntity);
    RTTI_METHOD(DetachEntity);

    RTTI_METHOD(IsManaged);
    RTTI_METHOD(IsTagged);
    RTTI_METHOD(IsSpawned);
    RTTI_METHOD(IsSpawning);
    RTTI_METHOD(GetEntity);
    RTTI_METHOD(GetTags);
    RTTI_METHOD(AssignTag);
    RTTI_METHOD(UnassignTag);

    RTTI_METHOD(IsPopulated);
    RTTI_METHOD(GetTagged);
    RTTI_METHOD(GetTaggedID);
    RTTI_METHOD(GetTaggedIDs);
    RTTI_METHOD(DespawnTagged);
    RTTI_METHOD(AttachTagged);
    RTTI_METHOD(DetachTagged);
});
