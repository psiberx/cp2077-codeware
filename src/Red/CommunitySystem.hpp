#pragma once

#include "Red/Addresses.hpp"

namespace Red
{
struct Community
{
    virtual void GetEntityIDs(DynArray<EntityID>& aOut) const = 0;
    virtual uint32_t GetEntityCount() const = 0;
    virtual bool IsOwnedEntity(EntityID aEntityID) = 0;
    virtual ~Community() = 0;
};
}

namespace Raw::CommunitySystem
{
constexpr auto ActivateCommunity = Core::RawVFunc<
    /* addr = */ 0x1A8,
    /* type = */ void (Red::gameICommunitySystem::*)(Red::EntityID aCommunityID, Red::CName aEntryName)>();

constexpr auto DeactivateCommunity = Core::RawVFunc<
    /* addr = */ 0x1B0,
    /* type = */ void (Red::gameICommunitySystem::*)(Red::EntityID aCommunityID, Red::CName aEntryName)>();

constexpr auto ResetCommunity = Core::RawVFunc<
    /* addr = */ 0x1C0,
    /* type = */ void (Red::gameICommunitySystem::*)(Red::EntityID aCommunityID, Red::CName aEntryName)>();

constexpr auto GetCommunity = Core::RawVFunc<
    /* addr = */ 0x220,
    /* type = */ void* (Red::gameICommunitySystem::*)(Red::WeakPtr<Red::Community>& aOut,
                                                      const Red::EntityID& aCommunityID)>();

constexpr auto Update = Core::RawFunc<
    /* addr = */ 0x140251834 - Red::Addresses::ImageBase, // FIXME
    /* type = */ void (*)(Red::gameICommunitySystem* aSystem, bool a2)>();
}
