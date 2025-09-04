#pragma once

#include "Red/CommunitySystem.hpp"

namespace App
{
struct PopulationSpawnerWrapper : Red::IScriptable
{
    PopulationSpawnerWrapper() = default;
    PopulationSpawnerWrapper(Red::SharedPtr<Red::Spawner> aSpawner);

    bool IsActive() const;
    bool IsInitialized() const;
    Red::TweakDBID GetRecordID() const;
    Red::CName GetAppearanceName() const;
    Red::WorldTransform GetTransform() const;
    Red::DynArray<Red::EntityID> GetActiveEntityIDs() const;
    Red::DynArray<Red::EntityID> GetRestoredEntityIDs() const;
    Red::DynArray<Red::EntityID> GetSpawnedEntityIDs() const;
    Red::DynArray<Red::EntityID> GetReservedEntityIDs() const;

    Red::SharedPtr<Red::Spawner> spawner;

    RTTI_IMPL_TYPEINFO(PopulationSpawnerWrapper);
    RTTI_IMPL_ALLOCATOR();
};
}

RTTI_DEFINE_CLASS(App::PopulationSpawnerWrapper, {
    RTTI_METHOD(IsActive);
    RTTI_METHOD(IsInitialized);
    RTTI_METHOD(GetRecordID);
    RTTI_METHOD(GetAppearanceName);
    RTTI_METHOD(GetTransform);
    RTTI_METHOD(GetActiveEntityIDs);
    RTTI_METHOD(GetRestoredEntityIDs);
    RTTI_METHOD(GetSpawnedEntityIDs);
    RTTI_METHOD(GetReservedEntityIDs);
});
