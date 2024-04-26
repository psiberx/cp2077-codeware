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
