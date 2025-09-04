#include "CommunityWrapper.hpp"

App::CommunityEntryWrapper::CommunityEntryWrapper(Red::SharedPtr<Red::Community> aCommunity,
                                                  Red::CommunityEntry* aEntry)
    : community(std::move(aCommunity))
    , entry(aEntry)
{
}

bool App::CommunityEntryWrapper::IsActive() const
{
    if (!entry)
        return false;

    return entry->active > 0;
}

Red::CName App::CommunityEntryWrapper::GetName() const
{
    if (!entry)
        return {};

    return entry->name;
}

Red::DynArray<Red::CName> App::CommunityEntryWrapper::GetPhases() const
{
    if (!entry)
        return {};

    return entry->phases;
}

Red::DynArray<Red::EntityID> App::CommunityEntryWrapper::GetRestoredEntityIDs() const
{
    if (!entry || !entry->spawner)
        return {};

    return entry->spawner->restoredEntityIDs;
}

Red::DynArray<Red::EntityID> App::CommunityEntryWrapper::GetSpawnedEntityIDs() const
{
    if (!entry || !entry->spawner)
        return {};

    return entry->spawner->spawnedEntityIDs;
}

Red::DynArray<Red::EntityID> App::CommunityEntryWrapper::GetSpawningEntityIDs() const
{
    if (!entry || !entry->spawner)
        return {};

    return entry->spawner->spawningStubIds;
}

Red::DynArray<Red::EntityID> App::CommunityEntryWrapper::GetReservedEntityIDs() const
{
    if (!entry || !entry->spawner)
        return {};

    return entry->spawner->reservedEntityIDs;
}

Red::Handle<Red::communitySpawnEntry> App::CommunityEntryWrapper::GetTemplateEntryData() const
{
    if (!entry || !entry->spawnEntry)
        return {};

    return Red::ToHandle(entry->spawnEntry);
}

App::CommunityWrapper::CommunityWrapper(Red::SharedPtr<Red::Community> aCommunity)
    : community(std::move(aCommunity))
{
}

Red::DynArray<Red::Handle<App::CommunityEntryWrapper>> App::CommunityWrapper::GetEntries() const
{
    if (!community)
        return {};

    Red::DynArray<Red::Handle<CommunityEntryWrapper>> out;

    for (const auto& entry : community->entries)
    {
        out.PushBack(Red::MakeHandle<CommunityEntryWrapper>(community, entry));
    }

    return out;
}

Red::DynArray<Red::EntityID> App::CommunityWrapper::GetActiveEntityIDs() const
{
    if (!community)
        return {};

    Red::DynArray<Red::EntityID> out;
    community->GetActiveEntityIDs(out);

    return out;
}

Red::Handle<Red::communityCommunityTemplateData> App::CommunityWrapper::GetTemplateData() const
{
    if (!community)
        return {};

    return community->template_;
}
