#pragma once

#include "Addresses.hpp"

namespace Raw::CGameFramework
{
constexpr auto InitializeGameInstance = Core::RawFunc<
    /* addr = */ Red::Addresses::CGameFramework_InitializeGameInstance,
    /* type = */ void (*)(void*, void*)>();
}
