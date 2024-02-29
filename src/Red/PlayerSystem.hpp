#pragma once

namespace Raw::PlayerSystem
{
constexpr auto OnPlayerSpawned = Core::RawFunc<
    /* addr = */ Red::AddressLib::PlayerSystem_OnPlayerSpawned,
    /* type = */ void* (*)(void*, void*, void*, void*)>();
}
