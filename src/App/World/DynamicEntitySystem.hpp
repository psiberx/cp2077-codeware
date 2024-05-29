#pragma once

#include "App/World/DynamicEntityEvent.hpp"
#include "App/World/DynamicEntitySpec.hpp"
#include "App/World/DynamicEntityState.hpp"
#include "App/World/DynamicEntitySystemPS.hpp"

namespace App
{
class DynamicEntitySystem : public Red::IGameSystem
{
public:
    DynamicEntitySystem() = default;

    [[nodiscard]] bool IsReady() const;
    [[nodiscard]] bool IsRestored() const;

    Red::EntityID CreateEntity(const DynamicEntitySpecPtr& aEntitySpec);
    bool DeleteEntity(Red::EntityID aEntityID);
    bool EnableEntity(Red::EntityID aEntityID);
    bool DisableEntity(Red::EntityID aEntityID);

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
    void DeleteTagged(Red::CName aTag);
    void EnableTagged(Red::CName aTag);
    void DisableTagged(Red::CName aTag);

    void RegisterListener(Red::CName aTag, const Red::Handle<Red::IScriptable>& aTarget, Red::CName aFunction);
    void UnregisterListener(Red::CName aTag, const Red::Handle<Red::IScriptable>& aTarget, Red::CName aFunction);
    void UnregisterListeners(Red::CName aTag);

protected:
    struct EventListener
    {
        Red::WeakHandle<Red::IScriptable> target;
        Red::CName function;
    };

    void OnWorldAttached(Red::world::RuntimeScene*) override;
    void OnStreamingWorldLoaded(Red::world::RuntimeScene*, uint64_t aRestored, const Red::JobGroup&) override;
    uint32_t OnBeforeGameSave(const Red::JobGroup&, void*) override;
    void OnAfterGameSave() override;
    void OnBeforeWorldDetach(Red::world::RuntimeScene*) override;
    void OnAfterWorldDetach() override;
    void OnEntitySpawnerEvent(Red::game::EntitySpawnerEventType aType, Red::EntityID aEntityID, Red::EntityID,
                              Red::EntityStub* aStub);

    bool SpawnFromEntityState(const DynamicEntityStatePtr& aEntityState);
    bool RespawnFromEntityState(const DynamicEntityStatePtr& aEntityState);
    bool DespawnFromEntityState(const DynamicEntityStatePtr& aEntityState);
    void RegisterPopulation(const App::DynamicEntityStatePtr& aEntityState, bool aRespawn = false);
    void RemovePopulation(const App::DynamicEntityStatePtr& aEntityState);
    void RemovePersistentState(const DynamicEntityStatePtr& aEntityState);
    void AcquireEntityStub(const App::DynamicEntityStatePtr& aEntityState, Red::EntityStubTokenPtr& aToken);
    void ResetEntityStub(const DynamicEntityStatePtr& aEntityState);
    void RemoveEntityStub(const DynamicEntityStatePtr& aEntityState);

    DynamicEntityStatePtr CreateEntityState(Red::EntityID aEntityID, const DynamicEntitySpecPtr& aEntitySpec);
    void RestoreEntityState(const DynamicEntityStatePtr& aEntityState);
    void AddEntityState(const DynamicEntityStatePtr& aEntityState);
    void UpdateTransientID(const DynamicEntityStatePtr& aEntityState);
    DynamicEntityStatePtr RemoveEntityState(Red::EntityID aEntityID);

    bool ValidateEntitySpec(const DynamicEntitySpecPtr& aEntitySpec);
    Red::TweakDBID ConvertTemplateToRecord(Red::RaRef<> aTemplate);

    void ProcessListeners(Red::EntityID aEntityID, DynamicEntityEventType aType, Red::DynArray<Red::CName>& aTags);
    void ProcessListeners(Red::EntityID aEntityID, DynamicEntityEventType aType);
    void ProcessListeners(Red::EntityID aEntityID, Red::game::EntitySpawnerEventType aType);

    bool m_ready;
    bool m_restored;

    std::shared_mutex m_entityStateLock;
    Core::Vector<DynamicEntityStatePtr> m_entityStates;
    Core::Map<Red::EntityID, DynamicEntityStatePtr> m_entityStateByID;
    Core::Map<Red::CName, Core::Set<Red::EntityID>> m_entityStatesByTag;

    std::shared_mutex m_listenersLock;
    Core::Map<Red::CName, Core::Vector<EventListener>> m_listenersByTag;

    Red::CClass* m_persistentStateType;
    Red::Handle<DynamicEntitySystemPS> m_persistentState;
    uint32_t m_spawnEventListenerID;

    Red::IPersistencySystem* m_persistencySystem;
    Red::IDynamicEntityIDSystem* m_entityIDSystem;
    Red::IEntityStubSystem* m_entityStubSystem;
    Red::IPopulationSystem* m_populationSystem;
    Red::IEntitySpawnerEventsBroadcaster* m_spawnEventBroadcaster;
    Red::worldRuntimeEntityRegistry* m_entityRegistry;
    Red::redTagSystem* m_entityTagSystem;

    RTTI_IMPL_TYPEINFO(App::DynamicEntitySystem);
    RTTI_IMPL_ALLOCATOR();
};
}

RTTI_DEFINE_CLASS(App::DynamicEntitySystem, {
    RTTI_GETTER(m_ready);
    RTTI_GETTER(m_restored);

    RTTI_METHOD(CreateEntity);
    RTTI_METHOD(DeleteEntity);
    RTTI_METHOD(EnableEntity);
    RTTI_METHOD(DisableEntity);

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
    RTTI_METHOD(DeleteTagged);
    RTTI_METHOD(EnableTagged);
    RTTI_METHOD(DisableTagged);

    RTTI_METHOD(RegisterListener);
    RTTI_METHOD(UnregisterListener);
    RTTI_METHOD(UnregisterListeners);
});
