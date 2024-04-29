#pragma once

#include "Red/EntitySpawner.hpp"

namespace Red
{
struct RuntimeSystemEntityAttachRequest
{
    RuntimeSystemEntityAttachRequest()
        : unk30(0)
        , unk32()
    {
    }

    RuntimeSystemEntityAttachRequest(Handle<Entity> aEntity)
        : entity(std::move(aEntity))
        , unk30(0)
        , unk32()
    {
    }

    Handle<Entity> entity;       // 00
    Handle<ISerializable> unk10; // 10
    Handle<ISerializable> unk20; // 20
    uint16_t unk30;              // 30
    uint8_t unk32[0x40 - 0x32];  // 32
};
RED4EXT_ASSERT_SIZE(RuntimeSystemEntityAttachRequest, 0x40);
RED4EXT_ASSERT_OFFSET(RuntimeSystemEntityAttachRequest, entity, 0x0);
}

namespace Raw::RuntimeScene
{
using Weather = Core::OffsetPtr<0x280, Red::Handle<Red::worldRuntimeSystemWeather>>;
}

namespace Raw::WeatherScriptInterface
{
using System = Core::OffsetPtr<0x40, Red::worldRuntimeSystemWeather*>;
}

namespace Raw::RuntimeSystemEntity
{
using Spawner = Core::OffsetPtr<0x58, Red::EntitySpawner*>;

constexpr auto AttachEntity = Core::RawFunc<
    /* addr = */ Red::AddressLib::RuntimeSystemEntity_AttachEntity,
    /* type = */ void (*)(Red::world::RuntimeSystemEntity* aSystem,
                          const Red::RuntimeSystemEntityAttachRequest& aRequest)>();

constexpr auto DetachEntity = Core::RawFunc<
    /* addr = */ Red::AddressLib::RuntimeSystemEntity_DetachEntity,
    /* type = */ void (*)(Red::world::RuntimeSystemEntity* aSystem,
                          const Red::Handle<Red::Entity>& aEntity)>();
}

namespace Raw::RuntimeSystemWeather
{
using CycleWeather = Core::OffsetPtr<0x8C, bool>;
using CurrentStateIndex = Core::OffsetPtr<0x90, uint32_t>;
using CurrentSource = Core::OffsetPtr<0x98, Red::CName>;
using PreviouseStateIndex = Core::OffsetPtr<0xB8, uint32_t>;

constexpr auto SetWeatherByName = Core::RawFunc<
    /* addr = */ Red::AddressLib::RuntimeSystemWeather_SetWeatherByName,
    /* type = */ bool (*)(Red::worldRuntimeSystemWeather* aSystem, Red::CName aWeather, Red::CName aSource,
                          float aBlendTime, uint32_t a5, uint32_t aPriority)>();

constexpr auto SetWeatherByIndex = Core::RawFunc<
    /* addr = */ Red::AddressLib::RuntimeSystemWeather_SetWeatherByIndex,
    /* type = */ bool (*)(Red::worldRuntimeSystemWeather* aSystem, uint32_t aIndex, Red::CName aSource,
                          float aBlendTime, float a5, uint32_t aPriority)>();

constexpr auto GetEnvironmentDefinition = Core::RawFunc<
    /* addr = */ Red::AddressLib::RuntimeSystemWeather_GetEnvironmentDefinition,
    /* type = */ void* (*)(Red::worldRuntimeSystemWeather* aSystem, Red::Handle<Red::worldEnvironmentDefinition>& aOut)>();

constexpr auto GetWeatherState = Core::RawFunc<
    /* addr = */ Red::AddressLib::RuntimeSystemWeather_GetWeatherState,
    /* type = */ void* (*)(Red::worldRuntimeSystemWeather* aSystem, Red::Handle<Red::worldWeatherState>& aOut)>();
}

namespace Raw::RuntimeEntityRegistry
{
constexpr auto RegisterEntity = Core::RawFunc<
    /* addr = */ Red::AddressLib::RuntimeEntityRegistry_RegisterEntity,
    /* type = */ void (*)(Red::world::RuntimeEntityRegistry* aSystem, Red::Entity* aEntity)>();

constexpr auto UnregisterEntity = Core::RawFunc<
    /* addr = */ Red::AddressLib::RuntimeEntityRegistry_UnregisterEntity,
    /* type = */ void (*)(Red::world::RuntimeEntityRegistry* aSystem, Red::Entity* aEntity)>();
}