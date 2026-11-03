#pragma once

// R18 B0. The engine core on macOS.
//
//   * CGameEngine. The Windows game keeps the engine singleton in a global that RED4ext's CGameEngine::Get() reads. No such
//     global has been found on Mac. The Mac InitEngine function (CBaseEngine::InitEngine, 0x3D9E494) receives the engine as
//     its first argument, so the hook on it records the pointer in a slot owned by this plugin, and that slot is what the
//     address hash of CGameEngine resolves to (Mac::StandInFor). Get() returns null until InitEngine has run.
//   * EngineTime_Frequency. The game has no double global either; its tick frequency comes from an accessor
//     (0x4D2C, uint64 ticks per second from mach_timebase_info). The stand-in is a double holding that value.
//   * Hook call counters (DIAG, CODEWARE_MAC_DIAG=1): every hook added in R18 counts its calls.

#include <atomic>
#include <cstdint>

#include <RED4ext/GameEngine.hpp>

namespace RED4ext
{
struct IScriptable;
}

namespace RED4ext::world
{
struct RuntimeScene;
}

namespace Mac
{
struct HookCounter
{
    const char* name;
    std::atomic<uint64_t> calls{0};
    std::atomic<int64_t> firstMs{-1}; // milliseconds since the plugin loaded at the first call
};

// Finds or registers the counter for a hook (at most 96). The name must be a string literal.
HookCounter& HookCount(const char* aName);

// Counts one call. Cheap enough for hot hooks.
void Hit(HookCounter& aCounter);

// "[diag] R18 counts@<when> name=calls ..." for every registered counter.
void LogHookCounts(const char* aWhen);

// Sum of the calls of all counters (to see whether any count changed).
uint64_t HookCountsTotal();

// The engine captured by the InitEngine hook, or null before it ran.
RED4ext::CGameEngine* Engine();

// Address of a plugin-owned stand-in for an address hash, or 0. Used by the Codeware resolver and by the SDK overlay.
uintptr_t StandInFor(uint32_t aHash);

// True for a hash that has a stand-in (used by the NOT_YET generator through macos/MacStandIns.inc).
bool HasStandIn(uint32_t aHash);

// Installs the engine hooks (InitEngine, LoadGatheredResources). Needs the resolver and the hooking driver.
bool InstallEngineHooks();

// True once ScriptValidator::Validate has returned in this process (the script bundle was validated).
bool ScriptsValidated();
void MarkScriptsValidated();

// SELFTEST R18. Menu-time checks of the engine core (engine capture, field offsets, EngineTime frequency).
void EngineSelfTest();

// SELFTEST R18. The runtime scene is only known at a world attach: checks that the system handle array of the scene
// (Handle<T> every 16 bytes, index from lib/Red/Engine/Mappings.hpp) holds the systems Codeware expects at those indexes.
void RuntimeSceneSelfTest(RED4ext::world::RuntimeScene* aScene);

// R18 B1. The InkSystem's system requests handler (the object whose IsPreGame script method CallbackSystem calls), or null
// when the InkSystem or the handler is not there yet. The handler is read at InkSystem+0x370 (the Windows offset, seen to hold
// it on Mac in r18d and r18e) and checked by class (RTTI IsA) before it is returned; the first success is logged.
RED4ext::IScriptable* InkRequestsHandler();

// SELFTEST R18. Dispatches trivial jobs the way Codeware does in production, without waiting: a queue from default
// parameters and a nested queue built from the group of the running job, then Capture and Join. JobDispatchTest runs once from
// the thread that runs codeware_postLoadScripts (an engine thread) and returns at once; JobDispatchCheck runs from the t+50s
// thread, only reads the counters the jobs incremented, and adds its checks to the R18 tally. JobHandle_Wait is not used: it
// only works on the main thread, outside jobs.
void JobDispatchTest();
void JobDispatchCheck();

// Called by the CGameFramework::InitializeGameInstance hook (the framework's GameInstance job body). aData is the job's
// closure; its first word is the CGameFramework. Records the framework (when its GameInstance is the one the constructor hook
// saw) and logs where the engine keeps it (DIAG).
void OnFrameworkJob(void* aData);

// The runtime system at an index of the engine's runtime scene (framework->unk18), or null when the engine, the framework or
// the scene does not exist yet. The scene layout is checked by RuntimeSceneSelfTest.
void* RuntimeSystemAt(uint32_t aIndex);

// R18 B1. False when the environment variable CODEWARE_MAC_NOHOOKS (comma list) names the hook group. For bisecting a boot.
bool HookEnabled(const char* aName);

// R18 B0. Whether a world system may turn itself on at a world attach. The systems are enabled one per boot while they are
// verified: the default list (kDefaultOn in MacEngine.cpp) holds the ones that passed; CODEWARE_MAC_SYSTEMS=<name>[,<name>]
// (or "all") adds more for a test boot.
bool SystemEnabled(const char* aName);

// R18 self-test tally shared by all R18 self-tests. R18Check records one check (a FAIL line when it is false);
// R18Summary prints "[selftest] R18 PASS@<when> (checks=N failed=M)".
void R18Check(bool aOk, const char* aWhat);
void R18Summary(const char* aWhen);
}
