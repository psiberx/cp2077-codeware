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
// Mac (R21, every slot checked against the game by body and call site): the community and spawner requests are Windows + 8. The
// Itanium ABI keeps the overloaded GetCommunity pair in declaration order and MSVC reverses it, so the by-reference GetCommunity is
// Mac 0x238 (an instruction-identical copy sits at 0x240) and GetSpawner stays at 0x260 (0x250 and 0x258 are identical copies);
// their address argument below is the Mac slot minus 8, which RawVFunc adds back. The WeakPtr results come back through x8 on Mac
// and the id moves up one register, so both get a wrapper with the Windows call shape.
// Game 2.5: gameCommunitySystem slots 0x1B0-0x1E8 and 0x258-0x268 are the 2.31 functions (same code or the same
// code with other registers; 0x220/0x228 fold into 0x1C2498). The Community/Spawner structs were not re-derived.
constexpr auto ActivateCommunity = Core::RawVFunc<
    /* addr = */ 0x1B0,
    /* type = */ void (Red::ICommunitySystem::*)(uint64_t aCommunityID, Red::CName aEntryName),
    /* verified = */ true>();

constexpr auto DeactivateCommunity = Core::RawVFunc<
    /* addr = */ 0x1B8,
    /* type = */ void (Red::ICommunitySystem::*)(uint64_t aCommunityID, Red::CName aEntryName),
    /* verified = */ true>();

constexpr auto SetCommunityPhase = Core::RawVFunc<
    /* addr = */ 0x1C0,
    /* type = */ void (Red::ICommunitySystem::*)(uint64_t aCommunityID, Red::CName aEntryName, Red::CName aPhaseName),
    /* verified = */ true>();

constexpr auto ResetCommunity = Core::RawVFunc<
    /* addr = */ 0x1C8,
    /* type = */ void (Red::ICommunitySystem::*)(uint64_t aCommunityID, Red::CName aEntryName),
    /* verified = */ true>();

#if defined(__APPLE__)
constexpr auto GetCommunityNative = Core::RawVFunc<
    /* addr = */ 0x230,
    /* type = */ Red::WeakPtr<Red::Community> (Red::ICommunitySystem::*)(const uint64_t& aCommunityID),
    /* verified = */ true>();

struct GetCommunityFn
{
    void* operator()(Red::ICommunitySystem* aSystem, Red::WeakPtr<Red::Community>& aOut, const uint64_t& aCommunityID) const
    {
        aOut = GetCommunityNative(aSystem, aCommunityID);
        return nullptr;
    }
};
inline constexpr GetCommunityFn GetCommunity{};
#else
constexpr auto GetCommunity = Core::RawVFunc<
    /* addr = */ 0x228,
    /* type = */ void* (Red::ICommunitySystem::*)(Red::WeakPtr<Red::Community>& aOut, 
                                                  const uint64_t& aCommunityID)>();
#endif

constexpr auto ActivateSpawner = Core::RawVFunc<
    /* addr = */ 0x1D8,
    /* type = */ void (Red::ICommunitySystem::*)(uint64_t aSpawnerID),
    /* verified = */ true>();

constexpr auto DeactivateSpawner = Core::RawVFunc<
    /* addr = */ 0x1E0,
    /* type = */ void (Red::ICommunitySystem::*)(uint64_t aSpawnerID),
    /* verified = */ true>();

constexpr auto ResetSpawner = Core::RawVFunc<
    /* addr = */ 0x1E8,
    /* type = */ void (Red::ICommunitySystem::*)(uint64_t aSpawnerID),
    /* verified = */ true>();

#if defined(__APPLE__)
constexpr auto GetSpawnerNative = Core::RawVFunc<
    /* addr = */ 0x258,
    /* type = */ Red::WeakPtr<Red::Spawner> (Red::ICommunitySystem::*)(uint64_t aSpawnerID),
    /* verified = */ true>();

struct GetSpawnerFn
{
    void* operator()(Red::ICommunitySystem* aSystem, Red::WeakPtr<Red::Spawner>& aOut, uint64_t aSpawnerID) const
    {
        aOut = GetSpawnerNative(aSystem, aSpawnerID);
        return nullptr;
    }
};
inline constexpr GetSpawnerFn GetSpawner{};
#else
constexpr auto GetSpawner = Core::RawVFunc<
    /* addr = */ 0x260,
    /* type = */ void* (Red::ICommunitySystem::*)(Red::WeakPtr<Red::Spawner>& aOut, uint64_t aSpawnerID)>();
#endif

constexpr auto Update = Core::RawFunc<
    /* addr = */ Red::AddressLib::CommunitySystem_Update,
    /* type = */ void (*)(Red::ICommunitySystem* aSystem, bool a2)>();
}
