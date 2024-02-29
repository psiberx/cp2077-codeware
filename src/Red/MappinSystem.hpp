#pragma once

namespace Raw::MappinSystem
{
constexpr auto SetPoiMappinPhase = Core::RawVFunc<
    /* addr = */ 0x1D0,
    /* type = */ void (Red::gamemappinsIMappinSystem::*)(const uint32_t aJournalPath,
                                                         const Red::gamedataMappinPhase aMappinPhase)>();

constexpr auto GetPoiMappinPhase = Core::RawVFunc<
    /* addr = */ 0x3C8,
    /* type = */ Red::gamedataMappinPhase (Red::gamemappinsIMappinSystem::*)(const uint32_t aJournalPath)>();
}

namespace Raw::PointOfInterestMappin
{
using JournalHash = Core::OffsetPtr<0x8C, uint32_t>;

constexpr auto SetPhase = Core::RawFunc<
    /* addr = */ Red::AddressLib::PointOfInterestMappin_SetPhase,
    /* type = */ bool (*)(void* aMappin, Red::gamedataMappinPhase aMappinPhase)>();
}
