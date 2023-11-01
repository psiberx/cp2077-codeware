#pragma once

#include "Red/Addresses.hpp"

namespace Raw::MappinSystem
{
constexpr auto SetPoiMappinPhase = Core::RawVFunc<
    /* addr = */ 0x1C8,
    /* type = */ void (Red::gamemappinsIMappinSystem::*)(const uint32_t aJournalPath,
                                                         const Red::gamedataMappinPhase aMappinPhase)>();

constexpr auto GetPoiMappinPhase = Core::RawVFunc<
    /* addr = */ 0x3C0,
    /* type = */ Red::gamedataMappinPhase (Red::gamemappinsIMappinSystem::*)(const uint32_t aJournalPath)>();
}

namespace Raw::PointOfInterestMappin
{
using JournalHash = Core::OffsetPtr<0x8C, uint32_t>;

constexpr auto SetPhase = Core::RawFunc<
    /* addr = */ Red::Addresses::PointOfInterestMappin_SetPhase,
    /* type = */ bool (*)(void* aMappin, Red::gamedataMappinPhase aMappinPhase)>();
}
