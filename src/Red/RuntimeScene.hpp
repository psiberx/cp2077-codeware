#pragma once

#include "Addresses.hpp"

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
    /* addr = */ 0x140B3935C - Red::Addresses::ImageBase,
    /* type = */ bool (*)(Red::world::RuntimeSystemWeather* aSystem, Red::CName aWeather, Red::CName aSource,
                          float aBlendTime, uint32_t a5, uint32_t aPriority)>();

constexpr auto SetWeatherByIndex = Core::RawFunc<
    /* addr = */ 0x140B37D48 - Red::Addresses::ImageBase,
    /* type = */ bool (*)(Red::world::RuntimeSystemWeather* aSystem, uint32_t aIndex, Red::CName aSource,
                          float aBlendTime, float a5, uint32_t aPriority)>();

constexpr auto GetWeatherState = Core::RawFunc<
    /* addr = */ 0x14013AC1C - Red::Addresses::ImageBase,
    /* type = */ void (*)(Red::world::RuntimeSystemWeather* aSystem, Red::world::WeatherState* aWeather, uint32_t aIndex)>();
}
