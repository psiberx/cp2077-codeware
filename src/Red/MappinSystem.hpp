#pragma once

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
