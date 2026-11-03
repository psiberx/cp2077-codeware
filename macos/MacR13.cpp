// DIAG and SELFTEST (CODEWARE_MAC_DIAG=1 only) for the Mac callback hooks.

#include "MacDiag.hpp"
#include "MacR13.hpp"
#include "MacEngine.hpp"
#include "MacR19.hpp"
#include "MacR20.hpp"
#include "MacR21.hpp"
#include "MacAddressResolver.hpp"
#include "Core/Hooking/HookHits.hpp"
#include "Support/macOS/Lifecycle.hpp"

#include "App/Callback/CallbackSystem.hpp"
#include "App/Callback/Events/KeyInputEvent.hpp"
#include "App/Callback/Events/ResourceEvent.hpp"
#include "App/Callback/MacHookStats.hpp"
#include "App/Scripting/ScriptableServiceContainer.hpp"

#include <algorithm>
#include <atomic>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <exception>
#include <string>
#include <thread>

namespace App
{
constexpr uint32_t MacSelfTestPathSlots = 3;

struct MacSelfTestSlot
{
    std::atomic<uint64_t> calls{0};
    std::atomic<uint32_t> recorded{0};
    std::atomic<uint64_t> path[MacSelfTestPathSlots]{};
};

extern "C" int cw_autotest_post_key(int aKeyCode, int aHoldMs); // macos/MacAutotest.mm
extern "C" int cw_autotest_key_series(int aKeyCode, int aIntervalMs, int aCount);
extern "C" void cw_autotest_stop_keys();
extern "C" void cw_autotest_dump_object(RED4ext::ISerializable* aObject, int aMaxDepth, int aArrayCap, const char* aLabel); // macos/MacAutotestDump.cpp

// SELFTEST R13. A native class with one static callback target. The self-test registers it with
// RegisterStaticCallback for Resource/Load and Resource/PostLoad. It counts the events and keeps the
// first three paths of each.
struct MacSelfTest : Red::IScriptable
{
    static constexpr uint32_t PathSlots = MacSelfTestPathSlots;
    using Slot = MacSelfTestSlot;

    inline static Slot load;
    inline static Slot postLoad;
    inline static std::atomic<uint64_t> otherEvents{0};

    // SELFTEST R14. Lets a diagnostic script print a line to stderr (used only by a throwaway test cache).
    static void Log(const Red::CString& aText)
    {
        std::fprintf(stderr, "%s\n", aText.c_str() ? aText.c_str() : "");
    }

    // R27. Test driver only (tools/autotest): hand a key press to the game's own view, inside the process (macos/MacAutotest.mm).
    static bool PostKey(int32_t aKeyCode)
    {
        return cw_autotest_post_key(aKeyCode, 90) != 0;
    }

    static bool PostKeys(int32_t aKeyCode, int32_t aIntervalMs, int32_t aCount)
    {
        return cw_autotest_key_series(aKeyCode, aIntervalMs, aCount) != 0;
    }

    static void StopKeys()
    {
        cw_autotest_stop_keys();
    }

    // R27. Test driver only (CP2077_AUTOTEST=1): dumps an object through the RTTI to stderr ("[dump]" lines), macos/MacAutotestDump.cpp.
    static void DumpObject(const Red::Handle<Red::ISerializable>& aObject, int32_t aMaxDepth, int32_t aArrayCap, const Red::CString& aLabel)
    {
        cw_autotest_dump_object(aObject.instance, aMaxDepth, aArrayCap, aLabel.c_str());
    }

    // The same for a scripted-hierarchy object (components, puppets, controllers: IScriptable in the script stubs).
    static void DumpScriptable(const Red::Handle<Red::IScriptable>& aObject, int32_t aMaxDepth, int32_t aArrayCap, const Red::CString& aLabel)
    {
        cw_autotest_dump_object(aObject.instance, aMaxDepth, aArrayCap, aLabel.c_str());
    }

    static void OnResource(const Red::Handle<ResourceEvent>& aEvent)
    {
        if (!aEvent)
        {
            otherEvents.fetch_add(1, std::memory_order_relaxed);
            return;
        }

        Slot* slot = nullptr;
        if (aEvent->eventName == Red::CName("Resource/Load"))
        {
            slot = &load;
        }
        else if (aEvent->eventName == Red::CName("Resource/PostLoad"))
        {
            slot = &postLoad;
        }
        else
        {
            otherEvents.fetch_add(1, std::memory_order_relaxed);
            return;
        }

        slot->calls.fetch_add(1, std::memory_order_relaxed);
        const auto index = slot->recorded.fetch_add(1, std::memory_order_relaxed);
        if (index < PathSlots)
        {
            const auto path = aEvent->GetPath();
            slot->path[index].store(path.path.hash, std::memory_order_relaxed);
        }
    }

    // SELFTEST R18 B1. One generic callback for every event kind: counts the deliveries per event name.
    static constexpr uint32_t MaxEventKinds = 32;
    inline static uint64_t eventHashes[MaxEventKinds]{};
    inline static const char* eventLabels[MaxEventKinds]{};
    inline static std::atomic<uint64_t> eventCounts[MaxEventKinds]{};
    inline static std::atomic<uint32_t> eventKinds{0};

    static void OnAnyEvent(const Red::Handle<CallbackSystemEvent>& aEvent)
    {
        if (!aEvent)
        {
            otherEvents.fetch_add(1, std::memory_order_relaxed);
            return;
        }

        const auto hash = aEvent->eventName.hash;
        if (hash == Red::CName("Input/Key").hash)
        {
            // The first key events log their modifier state, which checks InkSystem.keyboardState (+0x2F8 on Windows; the Mac
            // ProcessCharacterEvent 0x4887524 takes the address x0+0x2F8 as well, R26 sweep): hold Shift while pressing a key and expect shift=1.
            static std::atomic<int> s_keyLogs{0};
            if (s_keyLogs.fetch_add(1) < 16)
            {
                const auto* key = reinterpret_cast<const KeyInputEvent*>(aEvent.instance);
                std::fprintf(stderr, "[selftest] R18 key event key=%d action=%d shift=%d ctrl=%d alt=%d\n",
                             static_cast<int>(key->key), static_cast<int>(key->action), key->IsShiftDown() ? 1 : 0,
                             key->IsControlDown() ? 1 : 0, key->IsAltDown() ? 1 : 0);
            }
        }

        const auto kinds = eventKinds.load(std::memory_order_acquire);
        for (uint32_t i = 0; i < kinds; ++i)
        {
            if (eventHashes[i] == hash)
            {
                eventCounts[i].fetch_add(1, std::memory_order_relaxed);
                return;
            }
        }
        otherEvents.fetch_add(1, std::memory_order_relaxed);
    }

    RTTI_IMPL_TYPEINFO(App::MacSelfTest);
};
}

RTTI_DEFINE_CLASS(App::MacSelfTest, "CodewareMacSelfTest", {
    RTTI_ABSTRACT();
    RTTI_METHOD(OnResource);
    RTTI_METHOD(OnAnyEvent);
    RTTI_METHOD(Log);
    RTTI_METHOD(PostKey);
    RTTI_METHOD(PostKeys);
    RTTI_METHOD(StopKeys);
    RTTI_METHOD(DumpObject);
    RTTI_METHOD(DumpScriptable);
});

namespace
{
using namespace App::MacHookStats;

void LogCounters(const char* aWhen, const char* aName, const Counters& aCounters)
{
    MAC_DIAG( "[diag] R13 hook %s@%s t=%lldms calls=%llu resources=%llu dispatched=%llu noSystem=%llu first=", aName,
                 aWhen, static_cast<long long>(SinceLoadMs()), static_cast<unsigned long long>(aCounters.calls.load()),
                 static_cast<unsigned long long>(aCounters.resources.load()),
                 static_cast<unsigned long long>(aCounters.dispatched.load()),
                 static_cast<unsigned long long>(aCounters.noSystem.load()));
    const auto seen = std::min<uint32_t>(aCounters.firstSeen.load(), FirstPathCount);
    for (uint32_t i = 0; i < seen; ++i)
    {
        std::fprintf(stderr, "%s%016llx", i ? "," : "", static_cast<unsigned long long>(aCounters.firstPath[i].load()));
    }
    std::fprintf(stderr, "\n");
}

void LogAudio(const AudioTarget& aTarget)
{
    MAC_DIAG(
                 "[diag] R13 audio %s hash=%016llx load first=%lldms hits=%llu postload first=%lldms hits=%llu\n",
                 aTarget.name, static_cast<unsigned long long>(aTarget.hash),
                 static_cast<long long>(aTarget.firstLoadMs.load()),
                 static_cast<unsigned long long>(aTarget.loadHits.load()),
                 static_cast<long long>(aTarget.firstPostLoadMs.load()),
                 static_cast<unsigned long long>(aTarget.postLoadHits.load()));
}

void LogHookStats(const char* aWhen)
{
    MAC_DIAG( "[diag] R13 timing %s t=%lldms postLoadScripts=%lldms callbackSystemExists=%d\n", aWhen,
                 static_cast<long long>(SinceLoadMs()), static_cast<long long>(postLoadScriptsMs.load()),
                 App::CallbackSystem::Exists() ? 1 : 0);
    LogCounters(aWhen, "load", load);
    LogCounters(aWhen, "postload", postLoad);
    MAC_DIAG( "[diag] R13 hook attach@%s t=%lldms calls=%llu dispatched=%llu noSystem=%llu\n", aWhen,
                 static_cast<long long>(SinceLoadMs()), static_cast<unsigned long long>(attach.calls.load()),
                 static_cast<unsigned long long>(attach.dispatched.load()),
                 static_cast<unsigned long long>(attach.noSystem.load()));
    LogAudio(audioEventsMetadata);
    LogAudio(audioVoLanguageDataMap);
}

bool SlotOk(const App::MacSelfTest::Slot& aSlot)
{
    const auto calls = aSlot.calls.load();
    if (calls == 0)
    {
        return false;
    }
    const auto recorded = std::min<uint64_t>(aSlot.recorded.load(), App::MacSelfTest::PathSlots);
    for (uint64_t i = 0; i < recorded; ++i)
    {
        if (aSlot.path[i].load() == 0)
        {
            return false;
        }
    }
    return recorded > 0;
}

void LogSlot(const char* aName, const App::MacSelfTest::Slot& aSlot)
{
    MAC_DIAG( "[selftest] r13 callback %s calls=%llu paths=", aName,
                 static_cast<unsigned long long>(aSlot.calls.load()));
    const auto recorded = std::min<uint32_t>(aSlot.recorded.load(), App::MacSelfTest::PathSlots);
    for (uint32_t i = 0; i < recorded; ++i)
    {
        std::fprintf(stderr, "%s%016llx", i ? "," : "", static_cast<unsigned long long>(aSlot.path[i].load()));
    }
    std::fprintf(stderr, "\n");
}

void LogCallbackCounts(const char* aWhen)
{
    LogSlot("load", App::MacSelfTest::load);
    LogSlot("postload", App::MacSelfTest::postLoad);
    const bool ok = SlotOk(App::MacSelfTest::load) && SlotOk(App::MacSelfTest::postLoad);
    MAC_DIAG( "[selftest] r13 callback@%s ok=%d other=%llu\n", aWhen, ok ? 1 : 0,
                 static_cast<unsigned long long>(App::MacSelfTest::otherEvents.load()));
}

void RegisterCallbackChain()
{
    auto& system = App::CallbackSystem::Get();
    if (!system)
    {
        MAC_DIAG( "[selftest] r13 callback register ok=0 no CallbackSystem\n");
        return;
    }

    auto postLoad = system->RegisterStaticCallbackImpl(Red::CName("Resource/PostLoad"), Red::CName("CodewareMacSelfTest"),
                                                   Red::CName("OnResource"), {});
    auto load = system->RegisterStaticCallbackImpl(Red::CName("Resource/Load"), Red::CName("CodewareMacSelfTest"),
                                               Red::CName("OnResource"), {});
    MAC_DIAG( "[selftest] r13 callback register postload nonnull=%d static=%d load nonnull=%d static=%d\n",
                 postLoad ? 1 : 0, (postLoad && postLoad->IsStatic()) ? 1 : 0, load ? 1 : 0,
                 (load && load->IsStatic()) ? 1 : 0);
}

bool CallNodeRef(const char* aText, uint64_t& aHash)
{
    Red::CString text(aText);
    Red::ScriptRef<Red::CString> ref(false);
    ref.ref = &text;
    ref.managed = false;

    Red::NodeRef result{};
    const bool called = Red::CallGlobal("CreateNodeRef", result, ref);
    aHash = result.hash;
    return called;
}

void RunNodeRefSelfTest()
{
    constexpr auto kPath = "$/codeware/selftest";
    uint64_t first = 0;
    uint64_t second = 0;
    uint64_t empty = 1;
    const bool calledFirst = CallNodeRef(kPath, first);
    const bool calledSecond = CallNodeRef(kPath, second);
    const bool calledEmpty = CallNodeRef("", empty);
    const uint64_t fnv = Red::FNV1a64(kPath);
    const bool ok = calledFirst && calledSecond && calledEmpty && first != 0 && first == second && empty == 0;
    MAC_DIAG(
                 "[selftest] r13 noderef ok=%d called=%d%d%d first=%016llx second=%016llx equal=%d nonzero=%d "
                 "empty=%016llx fnv1a64=%016llx matchFnv=%d\n",
                 ok ? 1 : 0, calledFirst ? 1 : 0, calledSecond ? 1 : 0, calledEmpty ? 1 : 0,
                 static_cast<unsigned long long>(first), static_cast<unsigned long long>(second),
                 first == second ? 1 : 0, first != 0 ? 1 : 0, static_cast<unsigned long long>(empty),
                 static_cast<unsigned long long>(fnv), first == fnv ? 1 : 0);
}

bool CallRequire(const char* aVersion, bool& aResult)
{
    Red::CString version(aVersion);
    aResult = false;
    return Red::CallStatic("ArchiveXL", "Require", aResult, version);
}

void RunArchiveXLSelfTest()
{
    Red::CString version;
    const bool versionCalled = Red::CallStatic("ArchiveXL", "Version", version);
    const bool versionOk = versionCalled && version.c_str() && std::strcmp(version.c_str(), "1.26.1") == 0;

    bool low = false;
    bool high = false;
    const bool lowCalled = CallRequire("1.16.9", low);
    const bool highCalled = CallRequire("9.0.0", high);
    const bool requireOk = lowCalled && highCalled && low && !high;

    MAC_DIAG( "[selftest] r13 archivexl version ok=%d text=%s require1.16.9=%d require9.0.0=%d requireOk=%d ok=%d\n",
                 versionOk ? 1 : 0, version.c_str() ? version.c_str() : "", low ? 1 : 0, high ? 1 : 0,
                 requireOk ? 1 : 0, (versionOk && requireOk) ? 1 : 0);
}

// DIAG R14. Event names the CallbackSystem knows, for the callback counts.
const char* EventLabel(Red::CName aName, char* aBuffer, size_t aSize)
{
    struct Row
    {
        Red::CName name;
        const char* label;
    };
    static const Row kRows[] = {
        {Red::CName("Resource/Load"), "Resource/Load (script name Resource/Loaded)"},
        {Red::CName("Resource/PostLoad"), "Resource/PostLoad (script name Resource/Ready)"},
        {Red::CName("Entity/Attach"), "Entity/Attach"},
        {Red::CName("Entity/AfterAttach"), "Entity/AfterAttach (script name Entity/Attached)"},
        {App::CallbackSystem::SessionBeforeStartEventName, "Session/BeforeStart"},
        {App::CallbackSystem::SessionStartEventName, "Session/Start"},
        {App::CallbackSystem::SessionReadyEventName, "Session/Ready"},
        {App::CallbackSystem::SessionEndEventName, "Session/End"},
    };
    for (const auto& row : kRows)
    {
        if (row.name == aName)
        {
            return row.label;
        }
    }
    std::snprintf(aBuffer, aSize, "hash %016llx", static_cast<unsigned long long>(aName.hash));
    return aBuffer;
}

void LogR14(const char* aWhen)
{
    MAC_DIAG( "[diag] R14 t=%lldms @%s\n", static_cast<long long>(SinceLoadMs()), aWhen);

    if (App::CallbackSystem::Exists())
    {
        auto counts = App::CallbackSystem::Get()->MacCallbackCounts();
        std::sort(counts.begin(), counts.end(), [](const auto& aLeft, const auto& aRight) {
            return aLeft.first.hash < aRight.first.hash;
        });
        if (counts.empty())
        {
            MAC_DIAG( "[diag] R14 callbacks@%s none registered\n", aWhen);
        }
        for (const auto& [name, count] : counts)
        {
            char buffer[40];
            MAC_DIAG( "[diag] R14 callbacks@%s event=%s count=%zu\n", aWhen,
                         EventLabel(name, buffer, sizeof(buffer)), count);
        }
    }

    for (const auto& target : lizzieTargets)
    {
        MAC_DIAG(
                     "[diag] R14 target@%s %s hash=%016llx %s load hits=%llu reached=%llu first=%lldms postload "
                     "hits=%llu reached=%llu first=%lldms\n",
                     aWhen, target.name, static_cast<unsigned long long>(target.hash),
                     target.sector ? "sector" : "loaded", static_cast<unsigned long long>(target.hits[0].load()),
                     static_cast<unsigned long long>(target.reached[0].load()),
                     static_cast<long long>(target.firstReachedMs[0].load()),
                     static_cast<unsigned long long>(target.hits[1].load()),
                     static_cast<unsigned long long>(target.reached[1].load()),
                     static_cast<long long>(target.firstReachedMs[1].load()));
    }

    {
        std::lock_guard guard(handlerLock);
        if (handlers.empty())
        {
            MAC_DIAG( "[diag] R14 handler@%s none ran\n", aWhen);
        }
        for (const auto& [hash, entry] : handlers)
        {
            MAC_DIAG( "[diag] R14 handler@%s %s runs=%llu failed=%llu first=%lldms\n", aWhen,
                         entry.name.c_str(), static_cast<unsigned long long>(entry.runs),
                         static_cast<unsigned long long>(entry.failed), static_cast<long long>(entry.firstMs));
        }
    }

    MAC_DIAG( "[diag] R14 GetGameInstance@%s calls=%llu empty=%llu rescued=%llu\n", aWhen,
                 static_cast<unsigned long long>(getGameInstanceCalls.load()),
                 static_cast<unsigned long long>(getGameInstanceEmpty.load()),
                 static_cast<unsigned long long>(getGameInstanceRescued.load()));
}

template<typename F>
void Guarded(const char* aName, F&& aFunc)
{
    try
    {
        aFunc();
    }
    catch (const std::exception& ex)
    {
        MAC_DIAG( "[selftest] r13 %s exception %s\n", aName, ex.what());
    }
    catch (...)
    {
        MAC_DIAG( "[selftest] r13 %s exception\n", aName);
    }
}
}

void Mac::R13PostLoadScripts()
{
    // DIAG R14. Steam installs its crash handler after the plugin loads. Take the signals back, now and
    // twice more from a short-lived thread, so a fault in this boot leaves a report on stderr.
    Mac::InstallCrashDiag();
    std::thread([] {
        for (int i = 0; i < 4; ++i)
        {
            std::this_thread::sleep_for(std::chrono::seconds(3));
            Mac::InstallCrashDiag();
        }
    }).detach();

    if (!Mac::DiagEnabled())
    {
        return;
    }

    postLoadScriptsMs.store(SinceLoadMs());
    MAC_DIAG( "[diag] R13 postLoadScripts ran at t=%lldms since plugin load\n",
                 static_cast<long long>(postLoadScriptsMs.load()));
    Guarded("stats", [] { LogHookStats("postLoadScripts"); });

    // R14. The static-callback self-test would count as a listener for Resource/Load and Resource/PostLoad.
    // It stays off unless CODEWARE_R13_SELFTEST_CB is set.
    const bool callbackSelfTest = std::getenv("CODEWARE_R13_SELFTEST_CB") != nullptr;
    if (callbackSelfTest)
    {
        Guarded("callback", [] { RegisterCallbackChain(); });
    }
    Guarded("noderef", [] { RunNodeRefSelfTest(); });
    Guarded("archivexl", [] { RunArchiveXLSelfTest(); });

    // 50 s later, from a detached thread. The game holds the menu for 60 s after LoadScripts.
    std::thread([callbackSelfTest] {
        std::this_thread::sleep_for(std::chrono::seconds(50));
        Guarded("stats50", [callbackSelfTest] {
            LogHookStats("t+50s");
            if (callbackSelfTest)
            {
                LogCallbackCounts("t+50s");
            }
            LogR14("t+50s");
            Mac::LogHookCounts("t+50s");
            Core::HookHits::Dump("cw", "t+50s", Red::MacGameBase()); // R26: the call count of every attached hook
            Mac::R18LogEventCounts("t+50s");
            Mac::JobDispatchCheck();
            Mac::R18Summary("t+50s");
            Mac::R19CheckAtT50();
            Mac::R19Summary("t+50s");
            Mac::R20CheckAtT50();
            Mac::R20Summary("t+50s");
            Mac::R21CheckAtT50();
            Mac::R21Summary("t+50s");
        });
        std::fflush(stderr);

        // R18. For the in-game checklist (macos/INGAME_TESTS.md): every 30 s, for two hours, log the hook counts and the
        // callback deliveries again when they changed since the last line.
        uint64_t last = Mac::HookCountsTotal() + Mac::R18EventDeliveries();
        for (int i = 1; i <= 240; ++i)
        {
            std::this_thread::sleep_for(std::chrono::seconds(30));
            const uint64_t now = Mac::HookCountsTotal() + Mac::R18EventDeliveries();
            if (now == last)
            {
                continue;
            }
            last = now;
            char when[32];
            std::snprintf(when, sizeof(when), "t+%ds", 50 + i * 30);
            Guarded("periodic", [&when] {
                Mac::LogHookCounts(when);
                Mac::R18LogEventCounts(when);
            });
            std::fflush(stderr);
        }
    }).detach();
}

// SELFTEST R18 B1.
void Mac::R18RegisterEventCallbacks()
{
    if (!Mac::DiagEnabled())
    {
        return;
    }
    auto& system = App::CallbackSystem::Get();
    if (!system)
    {
        Mac::R18Check(false, "callback self-test: no CallbackSystem");
        return;
    }

    // CName::ToString() is empty for names that were never added to the game's name pool, so the labels come from this table.
    static const char* const kKnownEvents[] = {
        "Session/BeforeStart", "Session/BeforeEnd", "Session/End", "Session/BeforeSave", "Session/AfterSave", "Session/Start",
        "Session/Pause", "Session/Resume", "Session/Ready", "Resource/Load", "Resource/PostLoad", "Entity/Attach",
        "Entity/AfterAttach", "Entity/Initialize", "Entity/Reassemble", "Entity/Assemble", "Entity/Extract", "Entity/Detach",
        "Entity/Uninitialize", "Component/Toggle", "Vehicle/ToggleAuxLights", "Input/Key", "Input/Axis", "InkWidget/Spawn",
    };
    auto labelFor = [](Red::CName aName) -> std::string {
        for (const char* known : kKnownEvents)
        {
            if (Red::CName(known).hash == aName.hash)
            {
                return known;
            }
        }
        char buffer[32];
        std::snprintf(buffer, sizeof(buffer), "event-%016llx", static_cast<unsigned long long>(aName.hash));
        return buffer;
    };

    // Names must outlive the log lines: keep a copy of each event name's text.
    static std::string s_labels[App::MacSelfTest::MaxEventKinds];
    uint32_t registered = 0;
    uint32_t failed = 0;
    for (const auto& name : system->MacSupportedEventNames())
    {
        if (registered >= App::MacSelfTest::MaxEventKinds)
        {
            break;
        }
        auto handler = system->RegisterStaticCallbackImpl(name, Red::CName("CodewareMacSelfTest"), Red::CName("OnAnyEvent"), {});
        if (!handler || !handler->IsStatic() || !handler->IsRegistered())
        {
            ++failed;
            std::fprintf(stderr, "[selftest] R18 callback register FAILED for %s\n", labelFor(name).c_str());
            continue;
        }
        s_labels[registered] = labelFor(name);
        App::MacSelfTest::eventHashes[registered] = name.hash;
        App::MacSelfTest::eventLabels[registered] = s_labels[registered].c_str();
        ++registered;
        App::MacSelfTest::eventKinds.store(registered, std::memory_order_release);
    }
    Mac::R18Check(failed == 0 && registered > 0, "one script callback registered for every event kind");
    MAC_DIAG("[selftest] R18 callbacks registered=%u failed=%u\n", registered, failed);
}

uint64_t Mac::R18EventDeliveries()
{
    uint64_t total = 0;
    const auto kinds = App::MacSelfTest::eventKinds.load();
    for (uint32_t i = 0; i < kinds; ++i)
    {
        total += App::MacSelfTest::eventCounts[i].load();
    }
    return total;
}

void Mac::R18LogEventCounts(const char* aWhen)
{
    if (!Mac::DiagEnabled())
    {
        return;
    }
    char line[2048];
    size_t used = std::snprintf(line, sizeof(line), "[selftest] R18 callbacks@%s", aWhen);
    const auto kinds = App::MacSelfTest::eventKinds.load();
    for (uint32_t i = 0; i < kinds && used + 64 < sizeof(line); ++i)
    {
        const auto count = App::MacSelfTest::eventCounts[i].load();
        used += std::snprintf(line + used, sizeof(line) - used, " %s=%llu", App::MacSelfTest::eventLabels[i],
                              static_cast<unsigned long long>(count));
    }
    std::fprintf(stderr, "%s other=%llu\n", line, static_cast<unsigned long long>(App::MacSelfTest::otherEvents.load()));
}

// R14. The Mac equivalent of Windows' HookAfter<ScriptBundle::Destruct>: the scripts are loaded, so start
// the services. Each service class that is created or reloaded logs "[cw] service OnLoad <name>".
void Mac::R14StartServices()
{
    MAC_DIAG("[cw] R14 starting script services t=%lldms\n", static_cast<long long>(SinceLoadMs()));
    const auto started = SinceLoadMs();

    try
    {
        // ScriptingService (App::Application) subscribed: ScriptableServiceContainer::OnInitializeScripts().
        Mac::Lifecycle::RunServicesStart();
    }
    catch (const std::exception& ex)
    {
        std::fprintf(stderr, "[cw] R14 services OnInitializeScripts exception %s\n", ex.what());
    }
    catch (...)
    {
        std::fprintf(stderr, "[cw] R14 services OnInitializeScripts exception\n");
    }

    const auto finished = SinceLoadMs();
    MAC_DIAG( "[diag] R14 services OnInitializeScripts done at t=%lldms (took %lldms)\n",
                 static_cast<long long>(finished), static_cast<long long>(finished - started));
    if (Mac::DiagEnabled())
    {
        Guarded("r14", [] { LogR14("postLoadScripts-leave"); });
        Mac::LogHookCounts("postLoadScripts-leave");
    }
}
