#include "MacTrap.hpp"

#include "MacEngine.hpp"

#include <atomic>
#include <cstdio>
#include <cstring>
#include <dlfcn.h>
#include <mutex>
#include <unordered_set>

namespace
{
struct TrapRet
{
    uint64_t x0;
    uint64_t x1;
};

void TrapHit(uint32_t aHash, const void* aCaller);

// One instantiation per hash. The arguments of the call are ignored; x0 and x1 come back as zero.
template<uint32_t H>
__attribute__((noinline)) TrapRet TrapStub()
{
    TrapHit(H, __builtin_return_address(0));
    return TrapRet{0, 0};
}

// Same, for a function declared to return float or double: s0/d0 (v0) comes back as zero too.
template<uint32_t H>
__attribute__((noinline)) TrapRet TrapStubF()
{
    TrapHit(H, __builtin_return_address(0));
#if defined(__aarch64__)
    __asm__ volatile("movi v0.2d, #0" ::: "v0");
#endif
    return TrapRet{0, 0};
}

// Data traps read as zeros.
alignas(16) uint8_t g_zeroData[512];

struct Entry
{
    uint32_t hash;
    const void* address; // stub code, or g_zeroData for data hashes
    const char* name;
    bool isData;
};

#define TRAP_FUNC(h, name) {h, reinterpret_cast<const void*>(&TrapStub<h>), name, false},
#define TRAP_FLT(h, name) {h, reinterpret_cast<const void*>(&TrapStubF<h>), name, false},
#define TRAP_DATA(h, name) {h, g_zeroData, name, true},
const Entry kTable[] = {
#include "MacTrapTable.inc"
};
#undef TRAP_FUNC
#undef TRAP_FLT
#undef TRAP_DATA

constexpr size_t kCount = sizeof(kTable) / sizeof(kTable[0]);
std::atomic<bool> g_fired[kCount];
std::atomic<unsigned> g_hits{0};

const Entry* Find(uint32_t aHash)
{
    size_t lo = 0;
    size_t hi = kCount;
    while (lo < hi)
    {
        const size_t mid = (lo + hi) / 2;
        if (kTable[mid].hash < aHash)
            lo = mid + 1;
        else
            hi = mid;
    }
    return (lo < kCount && kTable[lo].hash == aHash) ? &kTable[lo] : nullptr;
}

void Describe(const void* aAddress, char* aOut, size_t aSize)
{
    Dl_info info{};
    if (aAddress && dladdr(aAddress, &info) && info.dli_fbase)
    {
        const char* file = info.dli_fname ? std::strrchr(info.dli_fname, '/') : nullptr;
        file = file ? file + 1 : (info.dli_fname ? info.dli_fname : "?");
        std::snprintf(aOut, aSize, "%s+0x%llx", file,
                      static_cast<unsigned long long>(reinterpret_cast<uintptr_t>(aAddress) -
                                                      reinterpret_cast<uintptr_t>(info.dli_fbase)));
        return;
    }
    std::snprintf(aOut, aSize, "?%p", aAddress);
}

void TrapHit(uint32_t aHash, const void* aCaller)
{
    const Entry* entry = Find(aHash);
    if (!entry)
    {
        return;
    }
    const size_t index = static_cast<size_t>(entry - kTable);
    if (g_fired[index].exchange(true))
    {
        return;
    }
    g_hits.fetch_add(1);
    char where[160];
    Describe(aCaller, where, sizeof(where));
    std::fprintf(stderr, "[cw] not on Mac yet: %s (hash %u) called from %s\n", entry->name, aHash, where);
}

const std::unordered_set<uintptr_t>& StubSet()
{
    static const std::unordered_set<uintptr_t> set = [] {
        std::unordered_set<uintptr_t> s;
        for (const auto& e : kTable)
        {
            s.insert(reinterpret_cast<uintptr_t>(e.address));
        }
        return s;
    }();
    return set;
}
}

uintptr_t Mac::TrapFor(uint32_t aHash)
{
    const Entry* entry = Find(aHash);
    if (!entry)
    {
        return 0;
    }
    if (entry->isData)
    {
        // A data hash is only noted when it is resolved; there is no call to hook into.
        const size_t index = static_cast<size_t>(entry - kTable);
        if (!g_fired[index].exchange(true))
        {
            g_hits.fetch_add(1);
            std::fprintf(stderr, "[cw] not on Mac yet: %s (hash %u, data, reads as zeros)\n", entry->name, aHash);
        }
    }
    return reinterpret_cast<uintptr_t>(entry->address);
}

bool Mac::IsTrapAddress(uintptr_t aAddress)
{
    const auto& set = StubSet();
    return set.find(aAddress) != set.end();
}

const char* Mac::TrapName(uint32_t aHash)
{
    const Entry* entry = Find(aHash);
    return entry ? entry->name : nullptr;
}

unsigned Mac::TrapTableSize()
{
    return static_cast<unsigned>(kCount);
}

unsigned Mac::TrapHitCount()
{
    return g_hits.load();
}

extern "C" uintptr_t codeware_mac_trap_for_hash(uint32_t aHash)
{
    // R18. A hash with a stand-in (MacStandIns.inc) is not a trap.
    if (const auto standIn = Mac::StandInFor(aHash))
    {
        return standIn;
    }
    const uintptr_t trap = Mac::TrapFor(aHash);
    if (!trap)
    {
        std::fprintf(stderr, "[cw] unknown address id %u (0x%x), not in the trap table, resolved to 0\n", aHash, aHash);
    }
    return trap;
}
