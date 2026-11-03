#pragma once

// R27. The installed RED4ext.dylib (the NightCity Console build; the same crash is in the 2026-10-03 crash reports, before any of our plugins existed)
// crashes at the very end of its own exit code on every normal quit of the game: App::Destruct opens a DetourTransaction to detach RED4ext's own hooks,
// the transaction is not committed because not every core hook is attached in the scoped mode (LoadScripts and InitScripts belong to the Frida script),
// and the transaction's destructor logs through spdlog::default_logger_raw(), which is already null (fault at logger+0x38, RED4ext.dylib+0xdb134).
// That code is not ours and is not patched.
//
// It runs after the last plugin has unloaded, so the last of our three plugins to unload leaves the process itself (after flushing the C streams):
// nothing else in the exit path is needed, the hooks die with the process. The rules:
//  - _exit is only ever called while the process is exiting. The signal is RED4ext's own game state API: each plugin registers a Shutdown game state
//    at Load, and its OnEnter marks the process as exiting. If that callback never fires on the Mac (it needs RED4ext's CGameApplication hook, which the
//    scoped mode does not attach), the fallback is the stack of the Unload call: it must contain libsystem_c's exit() (backtrace and dladdr). The log
//    line says which signal was used. An Unload that runs outside exit() (a reload, a failed load, one plugin unloaded alone) never calls _exit.
//    (An atexit flag was tried first and did not work: it was not set when RED4ext's destructor ran.)
//  - Each plugin keeps its state in the environment under CP2077_MAC_PLUGIN_<NAME>_STATE ("loaded" or "unloaded"); _exit waits for every plugin that
//    was loaded, and a plugin that was never loaded does not hold the others back.
//  - Each plugin flushes its own log files before it marks itself unloaded (the caller does that).
#include <RED4ext/RED4ext.hpp>

#include <atomic>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <dlfcn.h>
#include <execinfo.h>
#include <string>
#include <unistd.h>

namespace Mac
{
namespace Detail
{
inline std::atomic<bool>& ShutdownStateEntered()
{
    static auto* flag = new std::atomic<bool>(false); // never destroyed: it is read while the process exits
    return *flag;
}

inline const char*& PluginTag()
{
    static const char* tag = "?";
    return tag;
}

inline bool OnShutdownEnter(RED4ext::CGameApplication*)
{
    ShutdownStateEntered().store(true);
    std::fprintf(stderr, "[%s] R27 the Shutdown game state was entered\n", PluginTag());
    return true;
}

inline bool OnShutdownUpdate(RED4ext::CGameApplication*)
{
    return true;
}

inline bool OnShutdownExit(RED4ext::CGameApplication*)
{
    return true;
}

inline std::string StateKey(const char* aName)
{
    return std::string("CP2077_MAC_PLUGIN_") + aName + "_STATE";
}

// True when the caller runs inside exit() (the frames libsystem_c's exit and __cxa_finalize_ranges are on the stack).
inline bool CalledFromExit()
{
    void* frames[64];
    const int count = backtrace(frames, 64);
    for (int i = 0; i < count; ++i)
    {
        Dl_info info{};
        if (dladdr(frames[i], &info) && info.dli_sname && std::strcmp(info.dli_sname, "exit") == 0)
        {
            return true;
        }
    }
    return false;
}
} // namespace Detail

// Call from Load. aName is "AXL", "CW" or "TXL". Registers the Shutdown game state (the preferred signal that the process is exiting).
inline void MarkPluginLoaded(RED4ext::v1::PluginHandle aHandle, const RED4ext::v1::Sdk* aSdk, const char* aName)
{
    setenv(Detail::StateKey(aName).c_str(), "loaded", 1);
    Detail::PluginTag() = aName;
    static RED4ext::v1::GameState state{&Detail::OnShutdownEnter, &Detail::OnShutdownUpdate, &Detail::OnShutdownExit};
    const bool added = aSdk && aSdk->gameStates && aSdk->gameStates->Add &&
                       aSdk->gameStates->Add(aHandle, RED4ext::EGameStateType::Shutdown, &state);
    // A quiet session (CODEWARE_MAC_DIAG not 1) prints nothing for the normal case; the fallback notice and the exit lines always print.
    const char* diag = std::getenv("CODEWARE_MAC_DIAG");
    if (!added || (diag && std::strcmp(diag, "1") == 0))
    {
        std::fprintf(stderr, "[%s] R27 Shutdown game state %s\n", aName, added ? "registered" : "NOT available (the stack check is the signal)");
    }
}

// Call at the end of Unload (also on a repeated Unload call), after the plugin has flushed its own log files. Does not return when this was the last
// plugin and the process is exiting.
inline void ExitWhenAllPluginsUnloaded(const char* aName)
{
    setenv(Detail::StateKey(aName).c_str(), "unloaded", 1);

    for (const char* other : {"AXL", "CW", "TXL"})
    {
        const char* state = getenv(Detail::StateKey(other).c_str());
        if (state && std::strcmp(state, "unloaded") != 0)
        {
            return;
        }
    }

    const char* signal = Detail::ShutdownStateEntered().load() ? "the Shutdown game state" : (Detail::CalledFromExit() ? "exit() on the stack (fallback)" : nullptr);
    if (!signal)
    {
        return;
    }

    std::fprintf(stderr, "[%s] R27 last plugin unloaded while the process exits (signal: %s): leaving it (RED4ext's own exit code crashes)\n", aName, signal);
    std::fflush(nullptr);
    _exit(0);
}
} // namespace Mac
