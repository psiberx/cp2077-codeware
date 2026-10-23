#pragma once

#include <RED4ext/Scripting/Natives/Generated/ent/EntityTemplate.hpp>

namespace Red
{
struct EntitySpawner;

struct EntitySpawnerToken
{
    using AllocatorType = Memory::EngineAllocator;

    inline ~EntitySpawnerToken()
    {
        constexpr auto DestructToken = Core::RawFunc<
            /* addr = */ Red::AddressLib::EntitySpawnerToken_dtor,
            /* type = */ void (*)(Red::EntitySpawnerToken*)>();

        DestructToken(this);
    }

    uint64_t unk00;        // 00
    uint64_t unk10;        // 08
    Handle<Entity> entity; // 10
    bool detached;         // 20
    bool failed;           // 21
    bool aborted;          // 22
};
// Game 2.5: the token factory 0x5C178C allocates `mov ecx,0x28`; the dtor reads [rcx+0x10] (0xD93B75); 0x5C180E reads
// the failed flag `[r8+0x21]`.
RED4EXT_ASSERT_SIZE(EntitySpawnerToken, 0x28);
RED4EXT_ASSERT_OFFSET(EntitySpawnerToken, entity, 0x10);
RED4EXT_ASSERT_OFFSET(EntitySpawnerToken, failed, 0x21);

using EntitySpawnerCallback = FlexCallback<void (*)(const SharedPtr<EntitySpawnerToken>&)>;

struct EntitySpawnerRequest
{
    ResourcePath templatePath;      // 00
    WorldTransform transform;       // 10
    EntityID entityID;              // 30
    CName appearanceName;           // 38
    uint64_t unk40;                 // 40
    EntitySpawnerCallback callback; // 48
    bool detached;                  // 78
    bool dissolve;                  // 79
    uint8_t unk7A[0xE1 - 0x7A];     // 7A
    uint8_t priority{1};            // E1
    uint8_t unkE2;                  // E2
};
// Game 2.5: EntitySpawner_SpawnEntity 0x5C140C reads the callback `lea rdx,[rsi+0x48]` and priority [rsi+0xE1]; the
// token factory 0x5C1508 reads transform 0x10-0x2F, entityID 0x30, appearance 0x38, detached 0x78, 0x79-0x7B,
// 0x80-0xA0, 0xE0-0xE2 and word 0xE4 (all below 0xF0).
RED4EXT_ASSERT_SIZE(EntitySpawnerRequest, 0xF0);
RED4EXT_ASSERT_OFFSET(EntitySpawnerRequest, transform, 0x10);
RED4EXT_ASSERT_OFFSET(EntitySpawnerRequest, entityID, 0x30);
RED4EXT_ASSERT_OFFSET(EntitySpawnerRequest, callback, 0x48);
RED4EXT_ASSERT_OFFSET(EntitySpawnerRequest, detached, 0x78);
RED4EXT_ASSERT_OFFSET(EntitySpawnerRequest, priority, 0xE1);

struct EntitySpawner
{
    SharedPtr<EntitySpawnerToken> SpawnEntity(const EntitySpawnerRequest& aRequest)
    {
        constexpr auto SpawnEntity = Core::RawFunc<
            /* addr = */ Red::AddressLib::EntitySpawner_SpawnEntity,
            /* type = */ void* (*)(Red::EntitySpawner* aSpawner,
                                   Red::SharedPtr<Red::EntitySpawnerToken>& aToken,
                                   const Red::EntitySpawnerRequest& aRequest)>();

        Red::SharedPtr<Red::EntitySpawnerToken> token;
        SpawnEntity(this, token, aRequest);
        return token;
    }
};
}
