#pragma once

// R26. Per-hook call counts for the diagnostics (macOS only). Every attached hook is listed with the number of calls its detour has seen, so that
// a hook that never ran at the menu stands out ("0 menu hits" is unproven: the first real call may be in a save). The detour of a hook bumps a
// counter (one relaxed atomic add); the table is printed by Dump() from the plugin's own diagnostics thread, only when diagnostics are enabled.

#if defined(__APPLE__)

#include <atomic>
#include <cstdint>
#include <cstdio>
#include <mutex>
#include <vector>

namespace Core::HookHits
{
struct Site
{
    uintptr_t address;
    const void* handler;
};

struct Counter
{
    const void* handler;
    const std::atomic<uint64_t>* hits;
};

// Leaked on purpose: the detours can run while the process is shutting down.
inline std::mutex& Lock()
{
    static auto* lock = new std::mutex;
    return *lock;
}

inline std::vector<Site>& Sites()
{
    static auto* sites = new std::vector<Site>;
    return *sites;
}

inline std::vector<Counter>& Counters()
{
    static auto* counters = new std::vector<Counter>;
    return *counters;
}

inline void Attached(uintptr_t aAddress, const void* aHandler)
{
    std::lock_guard _(Lock());
    Sites().push_back({aAddress, aHandler});
}

inline void Bump(std::atomic<uint64_t>& aHits, const void* aHandler)
{
    if (aHits.fetch_add(1, std::memory_order_relaxed) == 0)
    {
        std::lock_guard _(Lock());
        Counters().push_back({aHandler, &aHits});
    }
}

// One line per attached hook: "[hooks] <plugin> <tag> rva=0x... calls=N".
inline void Dump(const char* aPlugin, const char* aTag, uintptr_t aImageBase)
{
    std::lock_guard _(Lock());
    size_t zero = 0;
    for (const auto& site : Sites())
    {
        uint64_t calls = 0;
        for (const auto& counter : Counters())
        {
            if (counter.handler == site.handler)
            {
                calls = counter.hits->load(std::memory_order_relaxed);
                break;
            }
        }
        zero += calls == 0 ? 1 : 0;
        std::fprintf(stderr, "[hooks] %s %s rva=0x%lx calls=%llu\n", aPlugin, aTag,
                     static_cast<unsigned long>(site.address >= aImageBase ? site.address - aImageBase : site.address),
                     static_cast<unsigned long long>(calls));
    }
    std::fprintf(stderr, "[hooks] %s %s attached=%zu with-calls=%zu zero-calls=%zu\n", aPlugin, aTag, Sites().size(),
                 Sites().size() - zero, zero);
}
} // namespace Core::HookHits

#endif
