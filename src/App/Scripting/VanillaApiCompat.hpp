#pragma once

#include "Core/Logging/LoggingAgent.hpp"

namespace App
{
// Game 2.5 ships its own version of Codeware's callback and service API (native types
// gameCallbackSystem, gameScriptableService, ... with the script names CallbackSystem,
// ScriptableService, ...; static natives GameInstance.GetCallbackSystem/GetScriptableServiceContainer).
// Its event set is a subset (Session/*, Resource/PostLoad, Resource/Ready): no Entity/*, so mods
// that use Codeware's events need Codeware's implementation bound to those script names.
//
// Evidence, game 2.5 exe 3.0.88.46235:
// - CRTTISystem::RegisterScriptName (vtable 0x3577168 slot 0x100 = 0x9764B8) overwrites both maps:
//   [this+0x150][script] = native, [this+0x180][native] = script.
// - GetClassByScriptName (slot 0x108 = 0x1B60D0) looks the script name up in [this+0x150] and calls
//   GetClass (0x281444) with the result, so the last registration wins.
// - The vanilla getter GameInstance.GetCallbackSystem (registered at 0x215843D, handler 0x2158680)
//   returns the vanilla singleton handle at 0x4CF6E30, not Codeware's system.
//
// Apply() maps each shared script name back to Codeware's native type and removes the vanilla
// GameInstance getters, leaving Codeware's (which take the same optional GameInstance parameter).
// On a game without the vanilla types it does nothing.
class VanillaApiCompat : public Core::LoggingAgent
{
public:
    static void Apply();
    static bool IsSharedScriptName(Red::CName aName);

private:
    static void ApplyResRefNatives();

    inline static bool s_resRefApplied = false;
    inline static bool s_scriptNamesApplied = false;
    inline static bool s_gettersApplied = false;
};
} // namespace App
