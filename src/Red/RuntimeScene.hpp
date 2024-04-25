#pragma once

namespace Raw::RuntimeScene
{
using Weather = Core::OffsetPtr<0x280, Red::Handle<Red::world::RuntimeSystemWeather>>;
}

namespace Raw::WeatherScriptInterface
{
using System = Core::OffsetPtr<0x40, Red::world::RuntimeSystemWeather*>;
}

namespace Raw::RuntimeSystemWeather
{
using CycleWeather = Core::OffsetPtr<0x8C, bool>;
using CurrentStateIndex = Core::OffsetPtr<0x90, uint32_t>;
using CurrentSource = Core::OffsetPtr<0x98, Red::CName>;
using PreviouseStateIndex = Core::OffsetPtr<0xB8, uint32_t>;

constexpr auto SetWeatherByName = Core::RawFunc<
    /* addr = */ Red::AddressLib::RuntimeSystemWeather_SetWeatherByName,
    /* type = */ bool (*)(Red::world::RuntimeSystemWeather* aSystem, Red::CName aWeather, Red::CName aSource,
                          float aBlendTime, uint32_t a5, uint32_t aPriority)>();

constexpr auto SetWeatherByIndex = Core::RawFunc<
    /* addr = */ Red::AddressLib::RuntimeSystemWeather_SetWeatherByIndex,
    /* type = */ bool (*)(Red::world::RuntimeSystemWeather* aSystem, uint32_t aIndex, Red::CName aSource,
                          float aBlendTime, float a5, uint32_t aPriority)>();

// constexpr auto GetWeatherState = Core::RawFunc<
//     /* addr = */ 0x14013AC1C - Red::Address::ImageBase,
//     /* type = */ void (*)(Red::world::RuntimeSystemWeather* aSystem, Red::world::WeatherState* aWeather, uint32_t aIndex)>();
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