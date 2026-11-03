// R18 B0. The engine core on macOS: the CGameEngine capture, the EngineTime frequency stand-in, the engine timing hooks and
// the hook call counters. See MacEngine.hpp.

#include "MacEngine.hpp"

#include "MacAddressResolver.hpp"
#include "MacDiag.hpp"
#include "MacR13.hpp"

#include "App/Callback/MacHookStats.hpp"
#include "Core/Hooking/HookingAgent.hpp"
#include "Red/GameEngine.hpp"
#include "Red/InkSystem.hpp"

#include <dlfcn.h>
#include <mach/mach.h>
#include <mach/mach_time.h>
#include <mach/mach_vm.h>

#include <chrono>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <memory>
#include <mutex>
#include <string>
#include <thread>

namespace
{
constexpr uint32_t kHashCGameEngine = 2549221846u;       // RED4ext Detail::AddressHashes::CGameEngine
constexpr uint32_t kHashEngineTimeFreq = 3151104823u;    // Red::AddressLib::EngineTime_Frequency
constexpr uintptr_t kRvaTickFrequency = 0x4B5C;          // uint64_t(), ticks per second from mach_timebase_info (cached)

RED4ext::CGameEngine* volatile s_engineSlot = nullptr;
double s_frequency = 0.0;
std::once_flag s_frequencyOnce;
std::atomic<bool> s_validated{false};

struct StandInRow
{
    uint32_t hash;
    const char* name;
};
constexpr StandInRow kStandIns[] = {
#define STANDIN(h, name) {h, name},
#include "MacStandIns.inc"
#undef STANDIN
};

// ---- hook counters
constexpr size_t kMaxCounters = 96;
Mac::HookCounter* s_counters[kMaxCounters];
std::atomic<size_t> s_counterCount{0};
std::mutex s_counterLock;

// ---- self-test tally
std::atomic<int> s_checks{0};
std::atomic<int> s_failed{0};

// The framework object (class CGameFramework). On Windows the SDK keeps it at engine +0x308. On Mac the framework job body
// (0x3F282C4) writes a different object to +0x310, and the framework itself is at +0x338 (2.3.1; 2.5.0: job body 0x1593BB8 stores +0x350, framework at +0x378): found in r18d by scanning the engine
// for the pointer the GameInstance job (0x3F0D900) works on (its closure's first word), whose GameInstance (+0x10) is the one
// the constructor hook saw and whose scene (+0x18) is the one passed to OnWorldAttached. Layout of the object itself matches the
// SDK: vtable +0x00, GameInstance* +0x10, runtime scene +0x18 (RuntimeScene, 0x4B8 bytes, built by the framework constructor).
constexpr uintptr_t kEngineFrameworkOffset = 0x378; // 2.5.0 (2.3.1: 0x338; CBaseEngine grew 0x40)

struct FrameworkView
{
    void* vtable;
    void* unk08;
    RED4ext::GameInstance* gameInstance;
    uintptr_t scene;
};

FrameworkView* FrameworkOf(RED4ext::CGameEngine* aEngine)
{
    return aEngine ? *reinterpret_cast<FrameworkView**>(reinterpret_cast<uintptr_t>(aEngine) + kEngineFrameworkOffset) : nullptr;
}

// The framework seen by the GameInstance job (Mac::OnFrameworkJob). Preferred over the engine slot once it is known.
std::atomic<FrameworkView*> s_jobFramework{nullptr};

FrameworkView* CurrentFramework(RED4ext::CGameEngine* aEngine)
{
    auto* job = s_jobFramework.load();
    return job ? job : FrameworkOf(aEngine);
}

// Reads memory that may be unmapped without faulting.
bool SafeRead(uintptr_t aAddress, void* aOut, size_t aSize)
{
    mach_vm_size_t got = 0;
    return aAddress && mach_vm_read_overwrite(mach_task_self(), aAddress, aSize, reinterpret_cast<mach_vm_address_t>(aOut), &got) ==
                           KERN_SUCCESS &&
           got == aSize;
}

// Trusted only when its GameInstance is the one the GameInstance constructor hook saw.
FrameworkView* ValidFramework()
{
    auto* fw = CurrentFramework(s_engineSlot);
    auto* gi = Red::MacGameInstance();
    return (fw && gi && fw->gameInstance == gi && fw->scene) ? fw : nullptr;
}

double FrequencyFromGame()
{
    using Fn = uint64_t (*)();
    const auto fn = reinterpret_cast<Fn>(Red::MacGameBase() + kRvaTickFrequency);
    return static_cast<double>(fn());
}

void ComputeFrequency()
{
    s_frequency = FrequencyFromGame();
    if (s_frequency <= 0.0)
    {
        mach_timebase_info_data_t info{};
        mach_timebase_info(&info);
        s_frequency = info.numer ? 1.0e9 * static_cast<double>(info.denom) / static_cast<double>(info.numer) : 1.0e9;
        std::fprintf(stderr, "[cw] engine: the game's tick frequency accessor returned 0, using mach_timebase_info\n");
    }
}

// ---- engine hooks
bool OnInitEngine(Red::CBaseEngine& aEngine, Red::CGameOptions& aOptions);
bool OnLoadGatheredResources(Red::CBaseEngine& aEngine);

class EngineHooks : public Core::HookingAgent
{
public:
    static bool Install()
    {
        const bool init = Hook<Raw::CBaseEngine::InitEngine>(&OnInitEngine);
        const bool gathered = Hook<Raw::CBaseEngine::LoadGatheredResources>(&OnLoadGatheredResources);
        // LoadGatheredResources is already hooked by another plugin (ArchiveXL hooks it; RED4ext allows one hook per target), so
        // the second attach is refused. The InitEngine begin/end lines bracket it.
        MAC_DIAG("[cw] engine hooks: InitEngine=%d LoadGatheredResources=%d%s\n", init ? 1 : 0, gathered ? 1 : 0,
                 gathered ? "" : " (taken by another plugin)");
        return init;
    }
};

bool OnInitEngine(Red::CBaseEngine& aEngine, Red::CGameOptions& aOptions)
{
    static auto& counter = Mac::HookCount("InitEngine");
    Mac::Hit(counter);

    s_engineSlot = static_cast<RED4ext::CGameEngine*>(&aEngine);
    const auto begin = App::MacHookStats::SinceLoadMs();
    MAC_DIAG("[cw] engine: InitEngine begin engine=%p t=%lldms\n", static_cast<void*>(&aEngine),
             static_cast<long long>(begin));

    const bool ok = Raw::CBaseEngine::InitEngine(aEngine, aOptions);

    const auto end = App::MacHookStats::SinceLoadMs();
    MAC_DIAG("[cw] engine: InitEngine end ok=%d t=%lldms (took %lldms)\n", ok ? 1 : 0, static_cast<long long>(end),
             static_cast<long long>(end - begin));
    return ok;
}

bool OnLoadGatheredResources(Red::CBaseEngine& aEngine)
{
    static auto& counter = Mac::HookCount("LoadGatheredResources");
    Mac::Hit(counter);

    const auto begin = App::MacHookStats::SinceLoadMs();
    const bool ok = Raw::CBaseEngine::LoadGatheredResources(aEngine);
    const auto end = App::MacHookStats::SinceLoadMs();
    MAC_DIAG("[cw] engine: LoadGatheredResources ok=%d t=%lldms (took %lldms)\n", ok ? 1 : 0, static_cast<long long>(end),
             static_cast<long long>(end - begin));
    return ok;
}
}

Mac::HookCounter& Mac::HookCount(const char* aName)
{
    std::lock_guard guard(s_counterLock);
    const auto count = s_counterCount.load();
    for (size_t i = 0; i < count; ++i)
    {
        if (std::strcmp(s_counters[i]->name, aName) == 0)
        {
            return *s_counters[i];
        }
    }
    static HookCounter pool[kMaxCounters];
    if (count >= kMaxCounters)
    {
        return pool[kMaxCounters - 1];
    }
    auto* counter = &pool[count];
    counter->name = aName;
    s_counters[count] = counter;
    s_counterCount.store(count + 1);
    return *counter;
}

void Mac::Hit(HookCounter& aCounter)
{
    if (!Mac::DiagEnabled())
    {
        return;
    }
    if (aCounter.calls.fetch_add(1, std::memory_order_relaxed) == 0)
    {
        aCounter.firstMs.store(App::MacHookStats::SinceLoadMs(), std::memory_order_relaxed);
    }
}

uint64_t Mac::HookCountsTotal()
{
    uint64_t total = 0;
    const auto count = s_counterCount.load();
    for (size_t i = 0; i < count; ++i)
    {
        total += s_counters[i]->calls.load();
    }
    return total;
}

void Mac::LogHookCounts(const char* aWhen)
{
    if (!Mac::DiagEnabled())
    {
        return;
    }
    char line[2048];
    size_t used = std::snprintf(line, sizeof(line), "[diag] R18 counts@%s t=%lldms", aWhen,
                                static_cast<long long>(App::MacHookStats::SinceLoadMs()));
    const auto count = s_counterCount.load();
    for (size_t i = 0; i < count && used + 64 < sizeof(line); ++i)
    {
        const auto* c = s_counters[i];
        used += std::snprintf(line + used, sizeof(line) - used, " %s=%llu@%lld", c->name,
                              static_cast<unsigned long long>(c->calls.load()), static_cast<long long>(c->firstMs.load()));
    }
    std::fprintf(stderr, "%s\n", line);
}

RED4ext::CGameEngine* Mac::Engine()
{
    return s_engineSlot;
}

uintptr_t Mac::StandInFor(uint32_t aHash)
{
    if (aHash == kHashCGameEngine)
    {
        return reinterpret_cast<uintptr_t>(const_cast<RED4ext::CGameEngine**>(&s_engineSlot));
    }
    if (aHash == kHashEngineTimeFreq)
    {
        std::call_once(s_frequencyOnce, ComputeFrequency);
        return reinterpret_cast<uintptr_t>(&s_frequency);
    }
    return 0;
}

bool Mac::HasStandIn(uint32_t aHash)
{
    for (const auto& row : kStandIns)
    {
        if (row.hash == aHash)
        {
            return true;
        }
    }
    return false;
}

bool Mac::InstallEngineHooks()
{
    return EngineHooks::Install();
}

bool Mac::ScriptsValidated()
{
    return s_validated.load();
}

void Mac::MarkScriptsValidated()
{
    s_validated.store(true);
}

void Mac::R18Check(bool aOk, const char* aWhat)
{
    s_checks.fetch_add(1);
    if (!aOk)
    {
        s_failed.fetch_add(1);
        MAC_DIAG( "[selftest] R18 FAIL %s\n", aWhat);
    }
}

void Mac::R18Summary(const char* aWhen)
{
    if (!Mac::DiagEnabled())
    {
        return;
    }
    const int failed = s_failed.load();
    MAC_DIAG( "[selftest] R18 %s@%s (checks=%d failed=%d)\n", failed == 0 ? "PASS" : "FAIL", aWhen, s_checks.load(),
                 failed);
}

void Mac::EngineSelfTest()
{
    if (!Mac::DiagEnabled())
    {
        return;
    }

    auto* engine = Engine();
    R18Check(engine != nullptr, "engine captured by the InitEngine hook");
    R18Check(RED4ext::CGameEngine::Get() == engine, "CGameEngine::Get() returns the captured engine through the address hash");
    if (engine)
    {
        R18Check(engine->scriptsLoaded, "engine scriptsLoaded (+0x54) is set after LoadScripts");
        R18Check(engine->engineState >= RED4ext::EEngineState::BaseInitialization && engine->engineState <= RED4ext::EEngineState::Running,
                 "engine state (+0x128) is BaseInitialization, Initialization or Running");
        MAC_DIAG("[selftest] R18 engine=%p state=%d scriptsLoaded=%d framework=%p\n", static_cast<void*>(engine),
                 static_cast<int>(engine->engineState), engine->scriptsLoaded ? 1 : 0, static_cast<void*>(CurrentFramework(engine)));
    }

    // EngineTime frequency: the stand-in must equal the value computed here from mach_timebase_info.
    const auto freqAddr = StandInFor(kHashEngineTimeFreq);
    mach_timebase_info_data_t info{};
    mach_timebase_info(&info);
    const double expected = 1.0e9 * static_cast<double>(info.denom) / static_cast<double>(info.numer);
    const double got = freqAddr ? *reinterpret_cast<const double*>(freqAddr) : 0.0;
    const double diff = got > expected ? got - expected : expected - got;
    R18Check(freqAddr != 0 && diff <= 1.0, "EngineTime frequency stand-in equals 1e9 * denom / numer");
    R18Check(*Raw::EngineTime::Frequency == got, "Raw::EngineTime::Frequency reads the stand-in through the resolver");
    MAC_DIAG("[selftest] R18 EngineTime frequency %.1f (mach_timebase %u/%u)\n", got, info.numer, info.denom);
}

namespace
{
// True when the pointer is readable and looks like a game object: its vtable's second slot is code in the game image.
bool LooksLikeGameObject(uintptr_t aObject)
{
    uintptr_t vtable = 0;
    uintptr_t slot = 0;
    if (!SafeRead(aObject, &vtable, sizeof(vtable)) || !vtable || !SafeRead(vtable + 8, &slot, sizeof(slot)) || !slot)
    {
        return false;
    }
    Dl_info info{};
    return dladdr(reinterpret_cast<void*>(slot & 0x0000007FFFFFFFFFULL), &info) != 0 && info.dli_fname != nullptr &&
           std::strstr(info.dli_fname, "Cyberpunk2077") != nullptr;
}

std::atomic<uintptr_t> s_inkHandlerOffset{0};
std::atomic<bool> s_inkHandlerLogged{false};
}

RED4ext::IScriptable* Mac::InkRequestsHandler()
{
    auto* ink = Red::InkSystem::Get();
    if (!ink)
    {
        return nullptr;
    }

    auto* klass = Red::GetClass("inkISystemRequestsHandler");
    if (!klass)
    {
        return nullptr;
    }

    const auto base = reinterpret_cast<uintptr_t>(ink);
    auto check = [&](uintptr_t aOffset) -> RED4ext::IScriptable* {
        uintptr_t instance = 0;
        if (!SafeRead(base + aOffset, &instance, sizeof(instance)) || !instance || (instance & 7) != 0 ||
            !LooksLikeGameObject(instance))
        {
            return nullptr;
        }
        auto* object = reinterpret_cast<RED4ext::IScriptable*>(instance);
        auto* type = object->GetType();
        return type && type->IsA(klass) ? object : nullptr;
    };

    const auto known = s_inkHandlerOffset.load();
    if (known)
    {
        return check(known);
    }

    // Only the Windows offset is used: r18d and r18e found the handler there (class checked), so nothing is scanned.
    uintptr_t found = 0;
    RED4ext::IScriptable* handler = check(0x370);
    if (handler)
    {
        found = 0x370;
    }

    if (handler)
    {
        s_inkHandlerOffset.store(found);
        if (!s_inkHandlerLogged.exchange(true))
        {
            MAC_DIAG( "[cw] R18 InkSystem=%p requestsHandler found at +0x%llx (Windows 0x370) instance=%p type=%s\n",
                         static_cast<void*>(ink), static_cast<unsigned long long>(found), static_cast<void*>(handler),
                         handler->GetType()->name.ToString());
        }
    }
    return handler;
}

// ---- job dispatch test (R18)
//
// Production dispatches in two shapes: a queue built from default parameters (JobQueue.DispatchJob from scripts, WaitForQueue)
// and a queue built from the JobGroup of the job that runs it (ScriptableServiceContainer::OnBeforeGameSave). Both are
// dispatched here from the thread that runs codeware_postLoadScripts, a thread that already creates handles and registers
// callbacks, and nothing waits: JobQueue::Dispatch is DispatchJob plus SyncWait, and SyncWait only chains the queue's handles
// (0x9D451C, it does not block). The closures only touch the atomics below; the check runs from the t+50s thread and only
// reads them.
//
// Who frees what:
//  * The closure is allocated with plain `new` in RED4ext::JobClosure::CreateTarget and freed with `delete` at the end of
//    JobClosure::HandleTarget, which is the job's handler, so both ends are plugin code.
//  * The engine never frees the closure. The dispatcher keeps the job (handler, target, family, 0x30 bytes) by value: in the ring
//    queue of the worker pool (0x9D7F80 copies it in, the worker 0x9DBDF8 copies it out onto its stack) or, when the job waits for
//    another handle, in a 0x38 byte continuation node (0x9D8720) that is released with operator delete after the job has been
//    queued (0x9D8324 to 0x9D8330). The runner 0x9D812C then calls handler(target, &group) and only works with the group's handle
//    and the queue afterwards. No path frees or reads the target. The game's own job bodies free their closures themselves
//    (0x3F0D900 does at 0x3F0D960), which is the contract the SDK's HandleTarget follows.
//  * The handles (JobInternalHandle, 0x28 bytes) belong to the game: Acquire and Release are the game's functions.
namespace
{
std::atomic<int> s_jobOuter{0};
std::atomic<int> s_jobGrouped{0};
std::atomic<int> s_jobNested{0};
std::atomic<bool> s_jobOnWorker{false};
std::atomic<bool> s_jobDispatched{false};
std::thread::id s_jobCaller;
Red::JobHandle* s_jobJoined = nullptr; // never destroyed; the t+50s check reads its pending counter
}

void Mac::JobDispatchTest()
{
    if (!Mac::DiagEnabled() || s_jobDispatched.exchange(true))
    {
        return;
    }

    // The dispatcher is created before InitEngine; do not call into the job runtime if it is not there.
    const auto cell = reinterpret_cast<void* const*>(Red::MacGameBase() + 0x9D0E550);
    if (*cell == nullptr)
    {
        MAC_DIAG( "[selftest] R18 jobs: the job dispatcher does not exist yet, test not started\n");
        Mac::R18Check(false, "the job dispatcher exists at postLoadScripts");
        return;
    }

    s_jobCaller = std::this_thread::get_id();

    // 1. A queue from default parameters.
    {
        Red::JobQueue queue{};
        queue.Dispatch([] {
            s_jobOnWorker.store(std::this_thread::get_id() != s_jobCaller);
            s_jobOuter.fetch_add(1);
        });
    }

    // 2. A queue built from the group of the job that runs it, dispatched inside that job (the OnBeforeGameSave shape),
    // then Capture and Join of the first queue's handle into a handle that outlives this function.
    {
        Red::JobQueue queue{};
        queue.Dispatch([](const Red::JobGroup& aGroup) {
            s_jobGrouped.fetch_add(1);
            Red::JobQueue nested{aGroup};
            nested.Dispatch([] { s_jobNested.fetch_add(1); });
        });

        auto handle = queue.Capture();
        s_jobJoined = new Red::JobHandle();
        s_jobJoined->Join(handle);
    }

    MAC_DIAG( "[selftest] R18 jobs: dispatched from the postLoadScripts thread, checked at t+50s\n");
}

void Mac::JobDispatchCheck()
{
    if (!s_jobDispatched.load())
    {
        return;
    }
    const bool joinedDone = s_jobJoined && s_jobJoined->internal && s_jobJoined->internal->unk18 == 0;
    MAC_DIAG( "[selftest] R18 jobs@t+50s: outer=%d grouped=%d nested=%d onWorker=%d joinedDone=%d\n", s_jobOuter.load(),
                 s_jobGrouped.load(), s_jobNested.load(), s_jobOnWorker.load() ? 1 : 0, joinedDone ? 1 : 0);
    Mac::R18Check(s_jobOuter.load() == 1, "a job dispatched through JobQueue ran exactly once");
    Mac::R18Check(s_jobOnWorker.load(), "the job ran on a job thread, not on the dispatching thread");
    Mac::R18Check(s_jobGrouped.load() == 1 && s_jobNested.load() == 1,
                  "a JobQueue built from a job's own group dispatched its nested job");
    Mac::R18Check(joinedDone, "a handle joined to the captured queue handle completed");
}

void Mac::OnFrameworkJob(void* aData)
{
    uintptr_t framework = 0;
    if (!SafeRead(reinterpret_cast<uintptr_t>(aData), &framework, sizeof(framework)) || !framework)
    {
        MAC_DIAG("[diag] R18 framework job: the closure %p holds no framework pointer\n", aData);
        return;
    }

    uintptr_t words[8]{};
    SafeRead(framework, words, sizeof(words));
    auto* engine = Engine();
    uintptr_t slot308 = 0, slot310 = 0;
    if (engine)
    {
        SafeRead(reinterpret_cast<uintptr_t>(engine) + 0x348, &slot308, sizeof(slot308));
        SafeRead(reinterpret_cast<uintptr_t>(engine) + 0x350, &slot310, sizeof(slot310));
    }
    MAC_DIAG("[diag] R18 framework job: closure=%p framework=0x%llx words=%llx %llx %llx %llx %llx engine+0x348=0x%llx "
             "engine+0x350=0x%llx MacGameInstance=%p\n",
             aData, static_cast<unsigned long long>(framework), static_cast<unsigned long long>(words[0]),
             static_cast<unsigned long long>(words[1]), static_cast<unsigned long long>(words[2]),
             static_cast<unsigned long long>(words[3]), static_cast<unsigned long long>(words[4]),
             static_cast<unsigned long long>(slot308), static_cast<unsigned long long>(slot310),
             static_cast<void*>(Red::MacGameInstance()));

    if (engine && Mac::DiagEnabled())
    {
        for (uintptr_t off = 0; off < 0x400; off += 8)
        {
            uintptr_t value = 0;
            if (SafeRead(reinterpret_cast<uintptr_t>(engine) + off, &value, sizeof(value)) && value == framework)
            {
                MAC_DIAG("[diag] R18 framework job: the engine holds the framework at +0x%llx\n",
                         static_cast<unsigned long long>(off));
            }
        }
    }

    if (words[2] == reinterpret_cast<uintptr_t>(Red::MacGameInstance()) && words[3])
    {
        s_jobFramework.store(reinterpret_cast<FrameworkView*>(framework));
        MAC_DIAG("[cw] engine: framework %p recorded (GameInstance +0x10 matches, scene +0x18 = 0x%llx)\n",
                 reinterpret_cast<void*>(framework), static_cast<unsigned long long>(words[3]));
    }
}

void* Mac::RuntimeSystemAt(uint32_t aIndex)
{
    auto* fw = ValidFramework();
    if (!fw || aIndex > 64)
    {
        return nullptr;
    }
    struct HandleSlot
    {
        void* instance;
        void* refCount;
    };
    return reinterpret_cast<const HandleSlot*>(fw->scene + aIndex * sizeof(HandleSlot))->instance;
}

void Mac::RuntimeSceneSelfTest(RED4ext::world::RuntimeScene* aScene)
{
    if (!Mac::DiagEnabled())
    {
        return;
    }
    auto* engine = Engine();
    auto* fw = CurrentFramework(engine);
    MAC_DIAG("[selftest] R18 world attach: scene=%p framework(+0x378)=%p gameInstance=%p scene18=0x%llx MacGameInstance=%p\n",
             static_cast<void*>(aScene), static_cast<void*>(fw), fw ? static_cast<void*>(fw->gameInstance) : nullptr,
             fw ? static_cast<unsigned long long>(fw->scene) : 0ULL, static_cast<void*>(Red::MacGameInstance()));
    R18Check(fw != nullptr, "engine framework exists at the first world attach");
    R18Check(FrameworkOf(engine) == fw, "the engine slot (+0x378) holds the framework seen by the GameInstance job");
    if (fw)
    {
        R18Check(fw->gameInstance == Red::MacGameInstance(),
                 "framework->gameInstance (+0x10) is the GameInstance seen by the constructor hook");
        R18Check(fw->scene == reinterpret_cast<uintptr_t>(aScene), "framework scene (+0x18) is the runtime scene passed to OnWorldAttached");
    }

    // The runtime scene keeps its systems as Handle<T> slots from offset 0: index * 16. Check the indexes Codeware uses.
    struct Expect
    {
        uint32_t index;
        const char* className;
    };
    static const Expect kExpect[] = {
        {10, "worldRuntimeSystemEntity"},
        {13, "worldRuntimeEntityRegistry"},
        {27, "worldRuntimeSystemWorldStreaming"},
        {31, "workWorkspotSystem"},
        {40, "worldRuntimeSystemWeather"},
    };
    for (const auto& e : kExpect)
    {
        auto* instance = static_cast<RED4ext::IScriptable*>(RuntimeSystemAt(e.index));
        const char* got = "<null>";
        if (instance)
        {
            auto* type = instance->GetType();
            got = type ? type->GetName().ToString() : "<no type>";
        }
        const bool ok = instance && std::strcmp(got, e.className) == 0;
        MAC_DIAG("[selftest] R18 runtime system [%u] expect %s got %s -> %s\n", e.index, e.className, got, ok ? "ok" : "no");
        R18Check(ok, e.className);
    }
}

void* Red::MacRuntimeSystemAt(uint32_t aIndex)
{
    return Mac::RuntimeSystemAt(aIndex);
}

// R22. Hand-off to the ArchiveXL plugin: the game has one hook slot per target, so Codeware owns the engine capture (InitEngine hook)
// and ArchiveXL looks these two functions up with dlsym.
extern "C" __attribute__((visibility("default"))) void* codeware_mac_runtime_system_at(uint32_t aIndex)
{
    return Mac::RuntimeSystemAt(aIndex);
}

namespace
{
// Systems that are on by default. StaticEntitySystem was ready in r18e. DynamicEntitySystem is in this list for the gate boots (R18
// release); CODEWARE_MAC_SYSTEMS_OFF=<name>[,<name>] turns one off again without a rebuild.
const char* const kDefaultOn[] = {"StaticEntitySystem", "DynamicEntitySystem", "OpenWorldSystem", "WorldStateSystem", nullptr};

bool NameInList(const char* aList, const char* aName)
{
    const std::string list = aList ? aList : "";
    size_t pos = 0;
    while (!list.empty() && pos <= list.size())
    {
        const auto end = list.find(',', pos);
        if (list.substr(pos, end == std::string::npos ? std::string::npos : end - pos) == aName)
        {
            return true;
        }
        if (end == std::string::npos)
        {
            break;
        }
        pos = end + 1;
    }
    return false;
}
}

bool Mac::HookEnabled(const char* aName)
{
    static const std::string env = [] {
        const char* v = std::getenv("CODEWARE_MAC_NOHOOKS");
        return std::string(v ? v : "");
    }();
    size_t pos = 0;
    while (!env.empty() && pos <= env.size())
    {
        const auto end = env.find(',', pos);
        if (env.substr(pos, end == std::string::npos ? std::string::npos : end - pos) == aName)
        {
            return false;
        }
        if (end == std::string::npos)
        {
            break;
        }
        pos = end + 1;
    }
    return true;
}

bool Mac::SystemEnabled(const char* aName)
{
    if (NameInList(std::getenv("CODEWARE_MAC_SYSTEMS_OFF"), aName))
    {
        return false;
    }
    for (const char* const* it = kDefaultOn; *it; ++it)
    {
        if (std::strcmp(*it, aName) == 0)
        {
            return true;
        }
    }
    static const std::string env = [] {
        const char* v = std::getenv("CODEWARE_MAC_SYSTEMS");
        return std::string(v ? v : "");
    }();
    if (env.empty())
    {
        return false;
    }
    if (env == "all")
    {
        return true;
    }
    // exact name inside a comma separated list
    size_t pos = 0;
    while (pos <= env.size())
    {
        const auto end = env.find(',', pos);
        const auto token = env.substr(pos, end == std::string::npos ? std::string::npos : end - pos);
        if (token == aName)
        {
            return true;
        }
        if (end == std::string::npos)
        {
            break;
        }
        pos = end + 1;
    }
    return false;
}

bool Red::MacSystemEnabled(const char* aName)
{
    return Mac::SystemEnabled(aName);
}
