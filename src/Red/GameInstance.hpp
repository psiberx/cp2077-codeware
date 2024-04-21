#pragma once

namespace Raw
{
constexpr auto GetScriptGameInstance = Core::RawFunc<
    /* addr = */ Red::AddressLib::GetScriptGameInstance,
    /* type = */ void (*)(Red::IScriptable* aContext, Red::CStackFrame* aFrame,
                          Red::ScriptGameInstance* aRet, Red::CBaseRTTIType* aType)>();
}
