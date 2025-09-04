#pragma once

#include "Red/CommunitySystem.hpp"

namespace App
{
struct CommunityEntryWrapper : Red::IScriptable
{
    CommunityEntryWrapper() = default;
    CommunityEntryWrapper(Red::SharedPtr<Red::Community> aCommunity, Red::CommunityEntry* aEntry);

    bool IsActive() const;
    Red::CName GetName() const;
    Red::DynArray<Red::CName> GetPhases() const;
    Red::DynArray<Red::EntityID> GetRestoredEntityIDs() const;
    Red::DynArray<Red::EntityID> GetSpawnedEntityIDs() const;
    Red::DynArray<Red::EntityID> GetSpawningEntityIDs() const;
    Red::DynArray<Red::EntityID> GetReservedEntityIDs() const;
    Red::Handle<Red::communitySpawnEntry> GetTemplateEntryData() const;

    Red::SharedPtr<Red::Community> community;
    Red::CommunityEntry* entry = nullptr;

    RTTI_IMPL_TYPEINFO(CommunityEntryWrapper);
    RTTI_IMPL_ALLOCATOR();
};

struct CommunityWrapper : Red::IScriptable
{
    CommunityWrapper() = default;
    CommunityWrapper(Red::SharedPtr<Red::Community> aCommunity);

    Red::DynArray<Red::Handle<CommunityEntryWrapper>> GetEntries() const;
    Red::DynArray<Red::EntityID> GetActiveEntityIDs() const;
    Red::Handle<Red::communityCommunityTemplateData> GetTemplateData() const;

    Red::SharedPtr<Red::Community> community;

    RTTI_IMPL_TYPEINFO(CommunityWrapper);
    RTTI_IMPL_ALLOCATOR();
};
}

RTTI_DEFINE_CLASS(App::CommunityEntryWrapper, {
    RTTI_METHOD(IsActive);
    RTTI_METHOD(GetName);
    RTTI_METHOD(GetPhases);
    RTTI_METHOD(GetRestoredEntityIDs);
    RTTI_METHOD(GetSpawnedEntityIDs);
    RTTI_METHOD(GetSpawningEntityIDs);
    RTTI_METHOD(GetReservedEntityIDs);
    RTTI_METHOD(GetTemplateEntryData);
});

RTTI_DEFINE_CLASS(App::CommunityWrapper, {
    RTTI_METHOD(GetEntries);
    RTTI_METHOD(GetActiveEntityIDs);
    RTTI_METHOD(GetTemplateData);
});