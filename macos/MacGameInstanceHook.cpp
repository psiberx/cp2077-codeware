// R14, R19. The GetGameInstance script native (0x1F42944), hooked like Windows Codeware does (ScriptingService::GetScriptGameInstance).
//
// The native reads CStackFrame+0x28 and builds the ScriptGameInstance from it. Codeware starts the script services (OnLoad,
// OnInitialize) from C++ with a synthetic frame, where that field is null, so the original returns an empty instance. Windows
// Codeware replaces the native (it advances the frame's code pointer and returns its own value). On Mac the replacement does
// the same, but returns the live GameInstance the constructor hook saw, built by the game's own builder (0x1F44968, the call
// the native makes): script natives that take the instance then find it. Both natives are twins (Windows 0xC56FB0): advance
// frame->code by one, test the frame context for the GameInstance magic, write a 24 byte ScriptGameInstance through the
// out pointer (a script native writes its result through aRet on both platforms; no x8 is involved). Until the live instance
// is known the original runs.
//
// R19 evidence: frames the original would have answered with the frame's instance are answered with the live one, and there
// is only one GameInstance, so nothing changes for them; the t+50s check reads the counters below.

#include "MacR13.hpp"
#include "MacDiag.hpp"

#include "App/Callback/MacHookStats.hpp"
#include "Core/Hooking/HookingAgent.hpp"
#include "Red/GameInstance.hpp"

#include <atomic>
#include <cstdio>

namespace
{
class GetGameInstanceHook : public Core::HookingAgent
{
public:
    static bool Install()
    {
        const bool ok = IsHooked<Raw::GetScriptGameInstance>() || Hook<Raw::GetScriptGameInstance>(&OnGetScriptGameInstance);
        MAC_DIAG_UNLESS(ok, "[cw] hook %s GetGameInstance target=%p\n", ok ? "installed" : "FAILED",
                     reinterpret_cast<void*>(Raw::GetScriptGameInstance.GetOriginalAddress()));
        return ok;
    }

private:
    static void OnGetScriptGameInstance(Red::IScriptable* aContext, Red::CStackFrame* aFrame, Red::ScriptGameInstance* aRet,
                                        Red::CBaseRTTIType* aType)
    {
        App::MacHookStats::getGameInstanceCalls.fetch_add(1, std::memory_order_relaxed);

        auto* instance = Red::MacGameInstance();
        if (!instance || !aFrame)
        {
            // Not known yet: the game's own native answers (an empty instance for a synthetic frame).
            Raw::GetScriptGameInstance(aContext, aFrame, aRet, aType);
            if (aRet && !aRet->instance)
            {
                App::MacHookStats::getGameInstanceEmpty.fetch_add(1, std::memory_order_relaxed);
            }
            return;
        }

        ++aFrame->code; // the native's own first step

        if (aRet)
        {
            Raw::MacScriptGameInstanceCtor(aRet, instance);
        }

        const auto live = App::MacHookStats::getGameInstanceRescued.fetch_add(1, std::memory_order_relaxed);
        if (live < 3)
        {
            MAC_DIAG("[cw] GetGameInstance answered with the live instance=%p (#%llu)\n",
                         static_cast<void*>(instance), static_cast<unsigned long long>(live + 1));
        }
    }
};
}

bool Mac::InstallGetGameInstanceHook()
{
    return GetGameInstanceHook::Install();
}
