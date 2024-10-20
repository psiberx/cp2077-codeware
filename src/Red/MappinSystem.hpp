#pragma once

namespace Red
{
struct MappinData
{
    uint64_t id;
    Handle<IMappin> instance;
};
}

namespace Raw::MappinSystem
{
using MappinsLock = Core::OffsetPtr<0x198, Red::SharedSpinLock>;
using MappinsData = Core::OffsetPtr<0x1A0, Red::SortedArray<Red::MappinData>>;

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
