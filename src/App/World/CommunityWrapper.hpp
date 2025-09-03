#pragma once

#include "Red/CommunitySystem.hpp"

namespace App
{
struct CommunityEntryWrapper : Red::IScriptable
{
    CommunityEntryWrapper(Red::SharedPtr<Red::Community> aCommunity, Red::CommunityEntry* aEntry)
        : community(aCommunity), entry(aEntry)
    {
    }

    CommunityEntryWrapper() = default;

    Red::CName GetName();
    bool IsActive();
    Red::DynArray<Red::CName> GetPhases();
    Red::DynArray<Red::EntityID> GetRestoredEntityIDs();
    Red::DynArray<Red::EntityID> GetSpawnedEntityIDs();
    Red::DynArray<Red::EntityID> GetSpawningEntityIDs();
    Red::DynArray<Red::EntityID> GetReservedEntityIDs();

    Red::SharedPtr<Red::Community> community;
    Red::CommunityEntry* entry;

    RTTI_IMPL_TYPEINFO(CommunityEntryWrapper);
    RTTI_IMPL_ALLOCATOR();
};

struct CommunityWrapper : Red::IScriptable
{
    CommunityWrapper(Red::SharedPtr<Red::Community> aCommunity)
        : community(aCommunity)
    {
    }

    CommunityWrapper() = default;

    Red::DynArray<Red::Handle<CommunityEntryWrapper>> GetEntries();
    Red::DynArray<Red::EntityID> GetActiveEntityIDs();

    Red::SharedPtr<Red::Community> community;

    RTTI_IMPL_TYPEINFO(CommunityWrapper);
    RTTI_IMPL_ALLOCATOR();
};

}

RTTI_DEFINE_CLASS(App::CommunityEntryWrapper, {
    RTTI_METHOD(GetName);
    RTTI_METHOD(IsActive);
    RTTI_METHOD(GetPhases);
    RTTI_METHOD(GetRestoredEntityIDs);
    RTTI_METHOD(GetSpawnedEntityIDs);
    RTTI_METHOD(GetSpawningEntityIDs);
    RTTI_METHOD(GetReservedEntityIDs);
});


RTTI_DEFINE_CLASS(App::CommunityWrapper, {
    RTTI_METHOD(GetEntries);
    RTTI_METHOD(GetActiveEntityIDs);
});
