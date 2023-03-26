#pragma once

#include "DynamicEntitySpec.hpp"
#include "DynamicEntityState.hpp"
#include "DynamicEntitySystemPS.hpp"

namespace App
{
class DynamicEntitySystem : public Red::IGameSystem
{
public:
    Red::EntityID CreateEntity(const DynamicEntitySpecPtr& aEntitySpec);
    bool DeleteEntity(Red::EntityID aEntityID);
    bool EnableEntity(Red::EntityID aEntityID);
    bool DisableEntity(Red::EntityID aEntityID);

    Red::DynArray<Red::CName> GetTags(Red::EntityID aEntityID);
    void AssignTag(Red::EntityID aEntityID, Red::CName aTag);
    void UnassignTag(Red::EntityID aEntityID, Red::CName aTag);

    bool IsPopulated(Red::CName aTag);
    Red::EntityID GetEntityID(Red::CName aTag);
    Red::DynArray<Red::EntityID> GetEntityIDs(Red::CName aTag);
    void DeleteTagged(Red::CName aTag);
    void EnableTagged(Red::CName aTag);
    void DisableTagged(Red::CName aTag);

protected:
    void OnWorldAttached(Red::world::RuntimeScene* aScene) override;
    bool OnGameRestored() override;
    uint32_t OnBeforeGameSave(const Red::JobGroup& aJobGroup, void* a2) override;
    void OnAfterGameSave() override;
    void OnBeforeWorldDetach(Red::world::RuntimeScene* aScene) override;
    void OnRegisterUpdates(Red::UpdateRegistrar* aRegistrar) override;
    void OnUpdateTick(Red::FrameInfo& aFrame, Red::JobQueue& aJobQueue);

    bool SpawnFromEntityState(const DynamicEntityStatePtr& aEntityState);
    bool RespawnFromEntityState(const DynamicEntityStatePtr& aEntityState);
    bool DespawnFromEntityState(const DynamicEntityStatePtr& aEntityState);
    void RegisterPopulation(const App::DynamicEntityStatePtr& aEntityState, bool aRespawn = false);
    void RemovePopulation(const App::DynamicEntityStatePtr& aEntityState);
    void RemovePersistentState(const DynamicEntityStatePtr& aEntityState);
    void RemoveEntityStub(const DynamicEntityStatePtr& aEntityState);

    DynamicEntityStatePtr CreateEntityState(Red::EntityID aEntityID, const DynamicEntitySpecPtr& aEntitySpec);
    void RestoreEntityState(const DynamicEntityStatePtr& aEntityState);
    void AddEntityState(const DynamicEntityStatePtr& aEntityState);
    void RemoveEntityState(const DynamicEntityStatePtr& aEntityState);

    Red::TweakDBID ConvertTemplateToRecord(Red::RaRef<> aTemplate);

    Core::Vector<DynamicEntityStatePtr> m_entityStates;
    Core::Map<Red::EntityID, DynamicEntityStatePtr> m_entityStateByID;
    Core::Map<Red::CName, Core::Set<Red::EntityID>> m_entityStatesByTag;

    Red::CClass* m_persistentStateType;
    Red::Handle<DynamicEntitySystemPS> m_persistentState;

    Red::TweakDB* m_tweakDB;
    Red::IPersistencySystem* m_persistencySystem;
    Red::IDynamicEntityIDSystem* m_entityIDSystem;
    Red::IEntityStubSystem* m_entityStubSystem;
    Red::IPopulationSystem* m_populationSystem;

    RTTI_IMPL_TYPEINFO(App::DynamicEntitySystem);
    RTTI_IMPL_ALLOCATOR(Red::Memory::RTTIAllocator);
};
}

RTTI_DEFINE_CLASS(App::DynamicEntitySystem, {
    RTTI_PARENT(Red::IGameSystem);

    RTTI_METHOD(CreateEntity);
    RTTI_METHOD(DeleteEntity);
    RTTI_METHOD(EnableEntity);
    RTTI_METHOD(DisableEntity);

    RTTI_METHOD(GetTags);
    RTTI_METHOD(AssignTag);
    RTTI_METHOD(UnassignTag);
    RTTI_METHOD(IsPopulated);
    RTTI_METHOD(GetEntityID);
    RTTI_METHOD(GetEntityIDs);
    RTTI_METHOD(DeleteTagged);
    RTTI_METHOD(EnableTagged);
    RTTI_METHOD(DisableTagged);
});
