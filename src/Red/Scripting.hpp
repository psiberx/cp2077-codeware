#pragma once

#include "Addresses.hpp"

namespace Raw::IScriptable
{
constexpr auto InitializeScriptData = Core::RawFunc<
    /* addr = */ Red::Addresses::IScriptable_InitializeScriptData,
    /* type = */ void (*)(Red::IScriptable* aInstance, Red::CClass* aClass, void* aValueHolder)>();
}
