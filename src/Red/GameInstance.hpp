#pragma once

#include "Addresses.hpp"

namespace Raw
{
constexpr auto GetScriptGameInstance = Core::RawFunc<
    /* addr = */ Red::Addresses::GetScriptGameInstance,
    /* type = */ void (*)(Red::IScriptable*, Red::CStackFrame* aFrame,
                          Red::ScriptGameInstance* aRet, Red::CBaseRTTIType* aType)>();
}
