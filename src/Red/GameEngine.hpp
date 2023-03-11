#pragma once

#include "Addresses.hpp"

namespace Raw::CBaseEngine
{
constexpr auto InitEngine = Core::RawFunc<
    /* addr = */ Red::Addresses::CBaseEngine_InitEngine,
    /* type = */ bool (*)(Red::CBaseEngine& aEngine, Red::CGameOptions& aOptions)>();
}
