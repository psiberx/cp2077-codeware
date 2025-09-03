#include "CommunityWrapper.hpp"

Red::CName App::CommunityEntryWrapper::GetName()
{
    if (!entry)
        return Red::CName();

    return entry->name;
}

bool App::CommunityEntryWrapper::IsActive()
{
    if (!entry)
        return false;

    return entry->active > 0;
}

int32_t App::CommunityEntryWrapper::GetActiveCount()
{
    if (!entry)
        return 0;

    return entry->active;
}

Red::DynArray<Red::CName> App::CommunityEntryWrapper::GetPhases()
{
    if (!entry)
        return {};

    return entry->phases;
}

Red::DynArray<Red::EntityID> App::CommunityEntryWrapper::GetRestoredEntityIDs()
{
    if (!entry || !entry->spawner)
        return {};

    return entry->spawner->restoredEntityIDs;
}

Red::DynArray<Red::EntityID> App::CommunityEntryWrapper::GetSpawnedEntityIDs()
{
    if (!entry || !entry->spawner)
        return {};

    return entry->spawner->spawnedEntityIDs;
}

Red::DynArray<Red::EntityID> App::CommunityEntryWrapper::GetSpawningEntityIDs()
{
    if (!entry || !entry->spawner)
        return {};

    return entry->spawner->spawningStubIds;
}

Red::DynArray<Red::EntityID> App::CommunityEntryWrapper::GetReservedEntityIDs()
{
    if (!entry || !entry->spawner)
        return {};

    return entry->spawner->reservedEntityIDs;
}

Red::DynArray<Red::Handle<App::CommunityEntryWrapper>> App::CommunityWrapper::GetEntries()
{
    if (!community)
        return {};

    Red::DynArray<Red::Handle<CommunityEntryWrapper>> out;

    for (const auto& entry : community->entries)
    {
        auto entryWrapper = Red::MakeHandle<CommunityEntryWrapper>();
        entryWrapper->community = community;
        entryWrapper->entry = entry;

        out.PushBack(entryWrapper);
    }

    return out;
}

Red::DynArray<Red::EntityID> App::CommunityWrapper::GetActiveEntityIDs()
{
    if (!community)
        return {};

    Red::DynArray<Red::EntityID> out;
    community->GetActiveEntityIDs(out);

    return out;
}

