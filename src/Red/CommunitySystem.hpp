#pragma once

namespace Red
{
struct CommunityEntrySpawner
{
    virtual ~CommunityEntrySpawner() = 0;

    DynArray<void*> unk08;                // 08
    DynArray<EntityID> restoredEntityIDs; // 18
    DynArray<EntityID> spawnedEntityIDs;  // 28
    DynArray<EntityID> spawningStubIds;   // 38
    DynArray<EntityID> reservedEntityIDs; // 48
};
RED4EXT_ASSERT_OFFSET(CommunityEntrySpawner, spawnedEntityIDs, 0x28);
RED4EXT_ASSERT_OFFSET(CommunityEntrySpawner, reservedEntityIDs, 0x48);

struct CommunityEntry
{
    virtual ~CommunityEntry() = 0;

    DynArray<CName> phases;          // 08
    EntityID communityID;            // 18
    CName name;                      // 20
    int32_t active;                  // 28
    uint16_t unk2C;                  // 2C
    uint8_t unk2E;                   // 2E
    CommunityEntrySpawner* spawner;  // 30
    void* unk38;                     // 38
    communitySpawnEntry* spawnEntry; // 40
};
RED4EXT_ASSERT_OFFSET(CommunityEntry, name, 0x20);
RED4EXT_ASSERT_OFFSET(CommunityEntry, unk2C, 0x2C);
RED4EXT_ASSERT_OFFSET(CommunityEntry, unk2E, 0x2E);
RED4EXT_ASSERT_OFFSET(CommunityEntry, spawner, 0x30);

struct Community
{
    using AllocatorType = Memory::DefaultAllocator;

    virtual void GetActiveEntityIDs(DynArray<EntityID>& aOut) const = 0;
    virtual uint32_t GetActiveEntityCount() const = 0;
    virtual bool IsOwnedEntity(EntityID aEntityID) = 0;
    virtual ~Community() = 0;

    EntityID id;                                      // 08
    bool active;                                      // 10
    bool initialized;                                 // 11
    DynArray<CommunityEntry*> entries;                // 18
    DynArray<CommunityEntry*> unk28;                  // 28
    Handle<communityCommunityTemplateData> template_; // 38
};
RED4EXT_ASSERT_OFFSET(Community, entries, 0x18);
RED4EXT_ASSERT_OFFSET(Community, template_, 0x38);

struct Spawner
{
    using AllocatorType = Memory::DefaultAllocator;

    virtual void GetActiveEntityIDs(DynArray<EntityID>& aOut) const = 0;
    virtual uint32_t GetActiveEntityCount() const = 0;
    virtual bool IsOwnedEntity(EntityID aEntityID) = 0;
    virtual ~Spawner() = 0;

    bool active;                          // 08
    bool initialized;                     // 09
    WorldTransform transform;             // 20
    TweakDBID recordID;                   // 40
    CName appearanceName;                 // 48
    uint32_t unk50;                       // 50
    bool unk54;                           // 54
    bool unk55;                           // 55
    bool unk56;                           // 56
    uint64_t unk58;                       // 58
    Handle<gamedataTweakDBRecord> record; // 60
    void* unk70;                          // 70
    DynArray<EntityID> restoredEntityIDs; // 78
    DynArray<EntityID> spawnedEntityIDs;  // 88
    DynArray<EntityID> reservedEntityIDs; // 98
};
RED4EXT_ASSERT_OFFSET(Spawner, transform, 0x20);
RED4EXT_ASSERT_OFFSET(Spawner, record, 0x60);
RED4EXT_ASSERT_OFFSET(Spawner, spawnedEntityIDs, 0x88);
RED4EXT_ASSERT_OFFSET(Spawner, reservedEntityIDs, 0x98);
}

namespace Raw::CommunitySystem
{
constexpr auto ActivateCommunity = Core::RawVFunc<
    /* addr = */ 0x1B0,
    /* type = */ void (Red::ICommunitySystem::*)(uint64_t aCommunityID, Red::CName aEntryName)>();

constexpr auto DeactivateCommunity = Core::RawVFunc<
    /* addr = */ 0x1B8,
    /* type = */ void (Red::ICommunitySystem::*)(uint64_t aCommunityID, Red::CName aEntryName)>();

constexpr auto SetCommunityPhase = Core::RawVFunc<
    /* addr = */ 0x1C0,
    /* type = */ void (Red::ICommunitySystem::*)(uint64_t aCommunityID, Red::CName aEntryName, Red::CName aPhaseName)>();

constexpr auto ResetCommunity = Core::RawVFunc<
    /* addr = */ 0x1C8,
    /* type = */ void (Red::ICommunitySystem::*)(uint64_t aCommunityID, Red::CName aEntryName)>();

constexpr auto GetCommunity = Core::RawVFunc<
    /* addr = */ 0x228,
    /* type = */ void* (Red::ICommunitySystem::*)(Red::WeakPtr<Red::Community>& aOut, 
                                                  const uint64_t& aCommunityID)>();

constexpr auto ActivateSpawner = Core::RawVFunc<
    /* addr = */ 0x1D8,
    /* type = */ void (Red::ICommunitySystem::*)(uint64_t aSpawnerID)>();

constexpr auto DeactivateSpawner = Core::RawVFunc<
    /* addr = */ 0x1E0,
    /* type = */ void (Red::ICommunitySystem::*)(uint64_t aSpawnerID)>();

constexpr auto ResetSpawner = Core::RawVFunc<
    /* addr = */ 0x1E8,
    /* type = */ void (Red::ICommunitySystem::*)(uint64_t aSpawnerID)>();

constexpr auto GetSpawner = Core::RawVFunc<
    /* addr = */ 0x260,
    /* type = */ void* (Red::ICommunitySystem::*)(Red::WeakPtr<Red::Spawner>& aOut, uint64_t aSpawnerID)>();

constexpr auto Update = Core::RawFunc<
    /* addr = */ Red::AddressLib::CommunitySystem_Update,
    /* type = */ void (*)(Red::ICommunitySystem* aSystem, bool a2)>();
}
