#pragma once

namespace Raw::CBaseEngine
{
constexpr auto InitEngine = Core::RawFunc<
    /* addr = */ Red::AddressLib::CBaseEngine_InitEngine,
    /* type = */ bool (*)(Red::CBaseEngine& aEngine, Red::CGameOptions& aOptions)>();

constexpr auto LoadGatheredResources = Core::RawFunc<
    /* addr = */ Red::AddressLib::CBaseEngine_LoadGatheredResources,
    /* type = */ bool (*)(Red::CBaseEngine& aEngine)>();
}

namespace Raw::EngineTime
{
constexpr auto Frequency = Core::RawPtr<
    /* addr = */ Red::AddressLib::EngineTime_Frequency,
    /* type = */ double>();
}