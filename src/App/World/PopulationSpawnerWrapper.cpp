#include "PopulationSpawnerWrapper.hpp"

App::PopulationSpawnerWrapper::PopulationSpawnerWrapper(Red::SharedPtr<Red::Spawner> aSpawner)
    : spawner(std::move(aSpawner))
{
}

Red::CName App::PopulationSpawnerWrapper::GetAppearanceName()
{
    if (!spawner)
        return {};

    return spawner->appearanceName;
}

Red::TweakDBID App::PopulationSpawnerWrapper::GetRecordID()
{
    if (!spawner)
        return {};

    return spawner->recordID;
}

Red::WorldTransform App::PopulationSpawnerWrapper::GetTransform()
{
    if (!spawner)
        return {};

    return spawner->transform;
}

bool App::PopulationSpawnerWrapper::IsActive()
{
    if (!spawner)
        return false;

    return spawner->active;
}

bool App::PopulationSpawnerWrapper::IsInitialized()
{
    if (!spawner)
        return false;

    return spawner->initialized;
}

Red::DynArray<Red::EntityID> App::PopulationSpawnerWrapper::GetActiveEntityIDs()
{
    if (!spawner)
        return {};

    Red::DynArray<Red::EntityID> out;
    spawner->GetActiveEntityIDs(out);
    return out;
}

Red::DynArray<Red::EntityID> App::PopulationSpawnerWrapper::GetRestoredEntityIDs()
{
    if (!spawner)
        return {};

    return spawner->restoredEntityIDs;
}

Red::DynArray<Red::EntityID> App::PopulationSpawnerWrapper::GetSpawnedEntityIDs()
{
    if (!spawner)
        return {};

    return spawner->spawnedEntityIDs;
}

Red::DynArray<Red::EntityID> App::PopulationSpawnerWrapper::GetReservedEntityIDs()
{
    if (!spawner)
        return {};

    return spawner->reservedEntityIDs;
}
