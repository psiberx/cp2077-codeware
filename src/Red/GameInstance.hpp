#pragma once

namespace Raw
{
constexpr auto GetScriptGameInstance = Core::RawFunc<
    /* addr = */ Red::AddressLib::GetScriptGameInstance,
    /* type = */ void (*)(Red::IScriptable* aContext, Red::CStackFrame* aFrame,
                          Red::ScriptGameInstance* aRet, Red::CBaseRTTIType* aType)>();

#if defined(__APPLE__)
// R14. Builds a ScriptGameInstance (instance, unk8 = 1, unk10 = 0) the way the Mac native does.
constexpr auto MacScriptGameInstanceCtor = Core::RawFunc<
    /* addr = */ Red::AddressLib::MacScriptGameInstanceCtor,
    /* type = */ void (*)(Red::ScriptGameInstance* aOut, Red::GameInstance* aInstance)>();
#endif
}
