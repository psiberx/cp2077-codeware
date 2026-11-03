#pragma once

// DIAG (CODEWARE_MAC_DIAG=1 only). Counters for the Mac callback hooks. The hook bodies write them from job
// threads; macos/MacR13.cpp logs them at postLoadScripts and again 50 s later. Without the flag every Note* function returns at once.

#if defined(__APPLE__)

#include <atomic>
#include "MacDiag.hpp"
#include <chrono>
#include <cstdint>
#include <cstdio>
#include <map>
#include <mutex>
#include <string>

namespace App::MacHookStats
{
constexpr uint32_t FirstPathCount = 5;

struct Counters
{
    std::atomic<uint64_t> calls{0};      // the hook ran
    std::atomic<uint64_t> noSystem{0};   // the hook ran before CallbackSystem existed
    std::atomic<uint64_t> resources{0};  // CResource objects found in the serializer list
    std::atomic<uint64_t> dispatched{0}; // events with at least one registered listener
    std::atomic<uint32_t> firstSeen{0};
    std::atomic<uint64_t> firstPath[FirstPathCount]{};
};

struct AudioTarget
{
    const char* name;
    uint64_t hash;
    std::atomic<int64_t> firstLoadMs{-1};
    std::atomic<uint64_t> loadHits{0};
    std::atomic<int64_t> firstPostLoadMs{-1};
    std::atomic<uint64_t> postLoadHits{0};
};

inline Counters load;
inline Counters postLoad;
inline Counters attach;

// Lizzie's two audio targets (Audio.reds). Hashes are Red::ResourcePath of the script strings.
inline AudioTarget audioEventsMetadata{"eventsmetadata.json",
                                       Red::ResourcePath::HashSanitized(R"(base\sound\event\eventsmetadata.json)")};
inline AudioTarget audioVoLanguageDataMap{"volanguagedatamap.json",
                                          Red::ResourcePath::HashSanitized(R"(base\localization\volanguagedatamap.json)")};

// Milliseconds since the plugin loaded. pluginLoadNs is set once in Main.
inline std::atomic<int64_t> pluginLoadNs{0};
inline std::atomic<int64_t> postLoadScriptsMs{-1};

inline int64_t NowNs()
{
    return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now().time_since_epoch())
        .count();
}

inline void MarkPluginLoad()
{
    pluginLoadNs.store(NowNs());
}

inline int64_t SinceLoadMs()
{
    const auto base = pluginLoadNs.load();
    return base ? (NowNs() - base) / 1000000 : -1;
}

inline void NoteResource(Counters& aCounters, uint64_t aPathHash)
{
    if (!Mac::DiagEnabled())
        return;
    aCounters.resources.fetch_add(1, std::memory_order_relaxed);
    const auto slot = aCounters.firstSeen.fetch_add(1, std::memory_order_relaxed);
    if (slot < FirstPathCount)
    {
        aCounters.firstPath[slot].store(aPathHash, std::memory_order_relaxed);
    }
}

// DIAG. Lizzie's 23 resource targets (Audio.reds and Resources.reds). For each event kind it counts
// the resources that matched the path ("hits") and the dispatches that reached at least one registered
// callback ("reached"). The 17 sector targets load in game, so 0 at the menu is expected.
struct LizzieTarget
{
    const char* name;
    uint64_t hash;
    bool sector; // true: Resource/Ready (PostLoad) in Lizzie's; false: Resource/Loaded (Load)
    std::atomic<uint64_t> hits[2]{};    // [0] Load, [1] PostLoad
    std::atomic<uint64_t> reached[2]{}; // dispatches that reached at least one callback
    std::atomic<int64_t> firstReachedMs[2]{{-1}, {-1}};
};

#define R14_PATH(_p) Red::ResourcePath::HashSanitized(_p)
#define R14_SECTOR(_n) \
    {_n, R14_PATH(R"(base\worlds\03_night_city\_compiled\default\)" _n ".streamingsector"), true}

inline LizzieTarget lizzieTargets[] = {
    {"eventsmetadata.json", R14_PATH(R"(base\sound\event\eventsmetadata.json)"), false},
    {"volanguagedatamap.json", R14_PATH(R"(base\localization\volanguagedatamap.json)"), false},
    {"mq006_02_finale.scene", R14_PATH(R"(base\quest\minor_quests\mq006\scenes\mq006_02_finale.scene)"), false},
    {"lizzies_bds_oblicej.scene", R14_PATH(R"(mod\arman3_lizzies_bds\quest\scenes\lizzies_bds_oblicej.scene)"), false},
    {"preview.dtex", R14_PATH(R"(mod\arman3_lizzies_bds\gameplay\gui\preview\preview.dtex)"), false},
    {"dlc6_apart_hey_gle_interactions.scene",
     R14_PATH(R"(dlc\dlc6_apart\loc_dlc6_apart_hey_gle\quest\scenes\dlc6_apart_hey_gle_interactions.scene)"), false},
    R14_SECTOR("exterior_-2_0_0_5"),
    R14_SECTOR("exterior_-9_6_1_2"),
    R14_SECTOR("exterior_-5_3_0_3"),
    R14_SECTOR("exterior_-3_1_0_4"),
    R14_SECTOR("exterior_-18_13_2_1"),
    R14_SECTOR("interior_4_16_3_1"),
    R14_SECTOR("exterior_-26_16_0_0"),
    R14_SECTOR("exterior_-26_15_0_0"),
    R14_SECTOR("interior_-52_32_0_0"),
    R14_SECTOR("interior_-21_26_0_0"),
    R14_SECTOR("interior_-11_13_0_1"),
    R14_SECTOR("exterior_-2_-1_0_1"),
    R14_SECTOR("exterior_-29_4_0_0"),
    R14_SECTOR("quest_1d80ac67f39864eb"),
    R14_SECTOR("exterior_-13_3_0_1"),
    R14_SECTOR("interior_51_-25_1_0"),
    R14_SECTOR("interior_25_-13_0_1"),
};

#undef R14_SECTOR
#undef R14_PATH

inline void NoteLizzieTarget(uint64_t aPathHash, bool aIsLoad, bool aReached)
{
    if (!Mac::DiagEnabled())
        return;
    const int kind = aIsLoad ? 0 : 1;
    for (auto& target : lizzieTargets)
    {
        if (aPathHash != target.hash)
        {
            continue;
        }
        target.hits[kind].fetch_add(1, std::memory_order_relaxed);
        if (aReached)
        {
            target.reached[kind].fetch_add(1, std::memory_order_relaxed);
            int64_t expected = -1;
            target.firstReachedMs[kind].compare_exchange_strong(expected, SinceLoadMs());
        }
    }
}

// DIAG. Script handler executions, keyed by the callback function name. Written from
// CallbackSystemHandler::ExecuteCallback. A handler runs only when its target matched, so this is rare.
struct HandlerEntry
{
    std::string name;
    bool started{false};
    uint64_t runs{0};
    uint64_t failed{0};
    int64_t firstMs{-1};
};

inline std::mutex handlerLock;
inline std::map<uint64_t, HandlerEntry> handlers;

// Logged once per function name, before the handler runs, so a crash inside a handler still shows which one.
inline void NoteHandlerStart(Red::CName aFunction)
{
    if (!Mac::DiagEnabled())
        return;
    std::lock_guard guard(handlerLock);
    auto& entry = handlers[aFunction.hash];
    if (!entry.started)
    {
        entry.started = true;
        const char* text = aFunction.ToString();
        entry.name = text ? text : "?";
        entry.firstMs = SinceLoadMs();
        MAC_DIAG( "[diag] R14 handler start %s t=%lldms\n", entry.name.c_str(),
                     static_cast<long long>(entry.firstMs));
    }
}

inline void NoteHandlerRun(Red::CName aFunction, bool aOk)
{
    if (!Mac::DiagEnabled())
        return;
    std::lock_guard guard(handlerLock);
    auto& entry = handlers[aFunction.hash];
    if (aOk)
    {
        ++entry.runs;
    }
    else
    {
        ++entry.failed;
    }
}

// DIAG. GetGameInstance native (0x1F42944) hook: calls seen and empty results rebuilt.
inline std::atomic<uint64_t> getGameInstanceCalls{0};
inline std::atomic<uint64_t> getGameInstanceEmpty{0};
inline std::atomic<uint64_t> getGameInstanceRescued{0};

inline void NoteAudioTarget(uint64_t aPathHash, bool aIsLoad)
{
    if (!Mac::DiagEnabled())
        return;
    for (auto* target : {&audioEventsMetadata, &audioVoLanguageDataMap})
    {
        if (aPathHash != target->hash)
        {
            continue;
        }
        auto& first = aIsLoad ? target->firstLoadMs : target->firstPostLoadMs;
        auto& hits = aIsLoad ? target->loadHits : target->postLoadHits;
        hits.fetch_add(1, std::memory_order_relaxed);
        int64_t expected = -1;
        first.compare_exchange_strong(expected, SinceLoadMs());
    }
}
}

#endif
