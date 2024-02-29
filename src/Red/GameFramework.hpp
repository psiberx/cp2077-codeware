#pragma once

namespace Raw::CGameFramework
{
constexpr auto InitializeGameInstance = Core::RawFunc<
    /* addr = */ Red::AddressLib::CGameFramework_InitializeGameInstance,
    /* type = */ void (*)(void*, void*)>();
}
