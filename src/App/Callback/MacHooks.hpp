#pragma once

// R18 B1. Shared plumbing for the Mac callback hooks. The hooks start at plugin load (App::InstallMacCallbackHooks), before
// the CallbackSystem class is registered, so every handler counts its call (DIAG, CODEWARE_MAC_DIAG=1) and returns
// until the CallbackSystem exists. The original always runs: the handlers are HookBefore or HookAfter observers.

#if defined(__APPLE__)

#include "MacEngine.hpp"
#include "MacDiag.hpp"

#include <cstdint>
#include <cstdio>

namespace App::MacHooks
{
inline void LogInstalled(const char* aName, uintptr_t aTarget, bool aOk)
{
    MAC_DIAG_UNLESS(aOk, "[cw] hook %s %s target=%p\n", aOk ? "installed" : "FAILED", aName, reinterpret_cast<void*>(aTarget));
}
}

#define MAC_HOOK_ENTER(aName)                                  \
    static auto& s_macHookCounter = ::Mac::HookCount(aName);   \
    ::Mac::Hit(s_macHookCounter);                              \
    if (!::App::CallbackSystem::Exists())                      \
    {                                                          \
        return;                                                \
    }

#else

#define MAC_HOOK_ENTER(aName)

#endif
