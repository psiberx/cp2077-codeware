#pragma once

#include "Red/Addresses.hpp"

namespace Red
{
struct EntityInitializeRequest
{
    WorldTransform transform;                                     // 00
    EntityID entityID;                                            // 20
    CName appearanceName;                                         // 28
    CName appearanceInternalName;                                 // 30
    bool isDynamic;                                               // 38
    void* unk40;                                                  // 40
    void* unk48;                                                  // 48
    void* unk50;                                                  // 50
    uint64_t unk58;                                               // 58
    uint64_t unk60;                                               // 60
    uint64_t unk68;                                               // 68
    Handle<ent::EntityParametersStorage> entityParams;            // 70
    DynArray<void*> unk80;                                        // 80
    Handle<population::PopulationSpawnParameter> populationParam; // 90
    uint64_t unkA0;                                               // A0
    uint64_t unkA8;                                               // A8
    net::PeerID controllingPeerID;                                // B0
    uint64_t unkB8;                                               // B8
    TweakDBID recordID;                                           // C0
    uint32_t unkC8;                                               // C8
    uint16_t unkCC;                                               // CC
};
RED4EXT_ASSERT_SIZE(EntityInitializeRequest, 0xD0);
RED4EXT_ASSERT_OFFSET(EntityInitializeRequest, entityID, 0x20);
RED4EXT_ASSERT_OFFSET(EntityInitializeRequest, entityParams, 0x70);
RED4EXT_ASSERT_OFFSET(EntityInitializeRequest, recordID, 0xC0);
RED4EXT_ASSERT_OFFSET(EntityInitializeRequest, unkCC, 0xCC);
}

namespace Raw::Entity
{
constexpr auto GetComponents = Core::RawFunc<
    /* addr = */ Red::Addresses::Entity_GetComponents,
    /* type = */ Red::DynArray<Red::Handle<Red::IComponent>>& (*)(Red::Entity* aEntity)>();

constexpr auto OnAssemble = Core::RawFunc<
    /* addr = */ Red::Addresses::Entity_OnAssemble,
    /* type = */ uintptr_t (*)(Red::Entity* aEntity, uintptr_t, uintptr_t)>();

constexpr auto Initialize = Core::RawFunc<
    /* addr = */ Red::Addresses::Entity_Initialize,
    /* type = */ void (*)(Red::Entity* aEntity, uintptr_t, Red::EntityInitializeRequest* aRequest)>();

constexpr auto Reassemble = Core::RawFunc<
    /* addr = */ Red::Addresses::Entity_Reassemble,
    /* type = */ void (*)(Red::Entity* aEntity, uintptr_t, uint64_t, uint64_t,
                          Red::DynArray<Red::Handle<Red::IComponent>>& aNewComponents,
                          Red::Handle<Red::ent::EntityParametersStorage>& aEntityParams)>();
}
