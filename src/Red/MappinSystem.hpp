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
// Game 2.5 (exe 3.0.88.46235): unchanged although the class grew by 64 bytes. Virtual 0x3B0 (0x2211400):
// `lea rsi,[rcx+0x198]` / `lea rdi,[rcx+0x1a0]`, as 2.31 0x1D1BC40; all 18 virtuals touching 0x198/0x1A0 match 2.31.
// Virtual slots 0x1D0 (0x2D4250C) and 0x3C8 (0x22125D0) have the same code as 2.31 (0x27AA144, 0x1D1C640).
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
// Game 2.5: PointOfInterestMappin_SetPhase 0x2D3F451 `mov edx,[rbx+0x8c]`.
using JournalHash = Core::OffsetPtr<0x8C, uint32_t>;

constexpr auto SetPhase = Core::RawFunc<
    /* addr = */ Red::AddressLib::PointOfInterestMappin_SetPhase,
    /* type = */ bool (*)(void* aMappin, Red::gamedataMappinPhase aMappinPhase)>();
}
