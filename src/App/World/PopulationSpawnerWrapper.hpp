#pragma once

#include "Red/CommunitySystem.hpp"

namespace App
{
struct PopulationSpawnerWrapper : Red::IScriptable
{
    PopulationSpawnerWrapper(Red::SharedPtr<Red::Spawner> aSpawner)
        : spawner(aSpawner)
    {
    }

    PopulationSpawnerWrapper() = default;

    Red::CName GetAppearanceName();
    Red::TweakDBID GetRecordID();
    Red::WorldTransform GetTransform();
    bool IsActive();
    bool IsInitialized();
    Red::DynArray<Red::EntityID> GetActiveEntityIDs();
    Red::DynArray<Red::EntityID> GetRestoredEntityIDs();
    Red::DynArray<Red::EntityID> GetSpawnedEntityIDs();
    Red::DynArray<Red::EntityID> GetReservedEntityIDs();

    Red::SharedPtr<Red::Spawner> spawner;

    RTTI_IMPL_TYPEINFO(PopulationSpawnerWrapper);
    RTTI_IMPL_ALLOCATOR();
};
}

RTTI_DEFINE_CLASS(App::PopulationSpawnerWrapper, {
    RTTI_METHOD(GetAppearanceName);
    RTTI_METHOD(GetRecordID);
    RTTI_METHOD(GetTransform);
    RTTI_METHOD(IsActive);
    RTTI_METHOD(IsInitialized);
    RTTI_METHOD(GetActiveEntityIDs);
    RTTI_METHOD(GetRestoredEntityIDs);
    RTTI_METHOD(GetSpawnedEntityIDs);
    RTTI_METHOD(GetReservedEntityIDs);
});
