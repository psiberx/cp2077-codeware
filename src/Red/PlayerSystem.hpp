#pragma once

#include "Addresses.hpp"

namespace Raw::PlayerSystem
{
constexpr auto OnPlayerSpawned = Core::RawFunc<
    /* addr = */ Red::Addresses::PlayerSystem_OnPlayerSpawned,
    /* type = */ void* (*)(void*, void*, void*, void*)>();
}
