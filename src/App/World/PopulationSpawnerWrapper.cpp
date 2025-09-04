#include "PopulationSpawnerWrapper.hpp"

App::PopulationSpawnerWrapper::PopulationSpawnerWrapper(Red::SharedPtr<Red::Spawner> aSpawner)
    : spawner(std::move(aSpawner))
{
}

bool App::PopulationSpawnerWrapper::IsActive() const
{
    if (!spawner)
        return false;

    return spawner->active;
}

bool App::PopulationSpawnerWrapper::IsInitialized() const
{
    if (!spawner)
        return false;

    return spawner->initialized;
}

Red::TweakDBID App::PopulationSpawnerWrapper::GetRecordID() const
{
    if (!spawner)
        return {};

    return spawner->recordID;
}

Red::CName App::PopulationSpawnerWrapper::GetAppearanceName() const
{
    if (!spawner)
        return {};

    return spawner->appearanceName;
}

Red::WorldTransform App::PopulationSpawnerWrapper::GetTransform() const
{
    if (!spawner)
        return {};

    return spawner->transform;
}

Red::DynArray<Red::EntityID> App::PopulationSpawnerWrapper::GetActiveEntityIDs() const
{
    if (!spawner)
        return {};

    Red::DynArray<Red::EntityID> out;
    spawner->GetActiveEntityIDs(out);

    return out;
}

Red::DynArray<Red::EntityID> App::PopulationSpawnerWrapper::GetRestoredEntityIDs() const
{
    if (!spawner)
        return {};

    return spawner->restoredEntityIDs;
}

Red::DynArray<Red::EntityID> App::PopulationSpawnerWrapper::GetSpawnedEntityIDs() const
{
    if (!spawner)
        return {};

    return spawner->spawnedEntityIDs;
}

Red::DynArray<Red::EntityID> App::PopulationSpawnerWrapper::GetReservedEntityIDs() const
{
    if (!spawner)
        return {};

    return spawner->reservedEntityIDs;
}
