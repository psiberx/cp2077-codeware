#include "MacHookChain.hpp"
#include "MacDiag.hpp"

#include <cstdio>
#include <dlfcn.h>
#include <mutex>
#include <string>
#include <vector>

// R22. See MacHookChain.hpp. The names below are built from HOOKCHAIN_SELF (the plugin: "archivexl" or "codeware"); each plugin exports
// <self>_mac_hook_chain_attach and keeps its own stubs and slots.

#ifndef HOOKCHAIN_SELF
#error "define HOOKCHAIN_SELF (archivexl or codeware) for MacHookChain.cpp"
#endif

#define HC_PASTE2(a, b) a##b
#define HC_PASTE(a, b) HC_PASTE2(a, b)
#define HC_STR2(x) #x
#define HC_STR(x) HC_STR2(x)

#define HC_HEADS HC_PASTE(HOOKCHAIN_SELF, _chain_heads)
#define HC_ATTACH HC_PASTE(HOOKCHAIN_SELF, _mac_hook_chain_attach)
#define HC_STUB_NAME(N) HC_PASTE(HC_PASTE(HOOKCHAIN_SELF, _chain_stub_), N)

namespace
{
constexpr unsigned kStubs = 192;
}

extern "C" __attribute__((visibility("hidden"))) void* HC_HEADS[kStubs];
void* HC_HEADS[kStubs] = {};

// One naked function per slot: load the slot, jump. Registers other than x16 stay as the game set them.
#define CHAIN_STUB(N)                                                                                     \
    extern "C" __attribute__((naked, visibility("hidden"), noinline)) void HC_STUB_NAME(N)()               \
    {                                                                                                      \
        __asm__("adrp x16, _" HC_STR(HC_HEADS) "@PAGE\n\t"                                                 \
                "add x16, x16, _" HC_STR(HC_HEADS) "@PAGEOFF\n\t"                                          \
                "ldr x16, [x16, #(" HC_STR(N) "*8)]\n\t"                                                   \
                "br x16\n");                                                                               \
    }
#include "MacHookStubs.inc"
#undef CHAIN_STUB

namespace
{
#define CHAIN_STUB(N) reinterpret_cast<void*>(&HC_STUB_NAME(N)),
void* const kStubFns[kStubs] = {
#include "MacHookStubs.inc"
};
#undef CHAIN_STUB

struct Slot
{
    uintptr_t target;
};

std::mutex g_lock;
Slot g_slots[kStubs];
unsigned g_used = 0;
unsigned g_chained = 0;

using PeerAttach = bool (*)(uintptr_t, void*, void**);

// The other plugins. A plugin that is not loaded (or is older than this protocol) has no such symbol.
const char* const kPeers[] = {"codeware_mac_hook_chain_attach", "archivexl_mac_hook_chain_attach"};
}

extern "C" __attribute__((visibility("default"))) bool HC_ATTACH(uintptr_t aTarget, void* aDetour, void** aOriginal)
{
    std::scoped_lock lock(g_lock);
    for (unsigned i = 0; i < g_used; ++i)
    {
        if (g_slots[i].target == aTarget)
        {
            if (aOriginal)
            {
                *aOriginal = HC_HEADS[i];
            }
            HC_HEADS[i] = aDetour;
            ++g_chained;
            return true;
        }
    }
    return false;
}

bool Mac::HookChain::Attach(uintptr_t aTarget, void* aDetour, void** aOriginal, AttachFn aRealAttach, void* aContext)
{
    {
        std::scoped_lock lock(g_lock);
        for (unsigned i = 0; i < g_used; ++i)
        {
            if (g_slots[i].target == aTarget)
            {
                // The same plugin hooks the target twice (not expected: its HookingAgent keeps one hook per target).
                if (aOriginal)
                {
                    *aOriginal = HC_HEADS[i];
                }
                HC_HEADS[i] = aDetour;
                MAC_DIAG("[chain] %s chained a second detour on %#lx\n", HC_STR(HOOKCHAIN_SELF),
                             static_cast<unsigned long>(aTarget));
                return true;
            }
        }
    }

    // Another plugin owns the target: put the detour on top of its chain.
    const std::string self = HC_STR(HC_ATTACH);
    for (const char* peer : kPeers)
    {
        if (self == peer)
        {
            continue;
        }
        if (auto fn = reinterpret_cast<PeerAttach>(dlsym(RTLD_DEFAULT, peer)))
        {
            if (fn(aTarget, aDetour, aOriginal))
            {
                MAC_DIAG("[chain] %s chained %#lx on a hook of %s (original=%p)\n", HC_STR(HOOKCHAIN_SELF),
                             static_cast<unsigned long>(aTarget), peer, aOriginal ? *aOriginal : nullptr);
                return true;
            }
        }
    }

    // New target: attach the stub through RED4ext. The slot holds the detour; RED4ext hands back the trampoline as the original.
    unsigned slot;
    {
        std::scoped_lock lock(g_lock);
        if (g_used >= kStubs)
        {
            std::fprintf(stderr, "[chain] %s is out of stubs, attaching %#lx directly (it cannot be shared)\n", HC_STR(HOOKCHAIN_SELF),
                         static_cast<unsigned long>(aTarget));
            return aRealAttach(aTarget, aDetour, aOriginal, aContext);
        }
        slot = g_used++;
        HC_HEADS[slot] = aDetour;
        g_slots[slot].target = aTarget;
    }

    if (!aRealAttach(aTarget, kStubFns[slot], aOriginal, aContext))
    {
        std::scoped_lock lock(g_lock);
        if (slot + 1 == g_used)
        {
            --g_used;
        }
        g_slots[slot].target = 0;
        HC_HEADS[slot] = nullptr;
        return false;
    }
    return true;
}

bool Mac::HookChain::Owns(uintptr_t aTarget)
{
    std::scoped_lock lock(g_lock);
    for (unsigned i = 0; i < g_used; ++i)
    {
        if (g_slots[i].target == aTarget)
        {
            return true;
        }
    }
    return false;
}

unsigned Mac::HookChain::ChainedCount()
{
    std::scoped_lock lock(g_lock);
    return g_chained;
}

unsigned Mac::HookChain::StubsInUse()
{
    std::scoped_lock lock(g_lock);
    return g_used;
}

// ---------------------------------------------------------------------------------------------------------------------------------
// Shared instances (see MacHookChain.hpp).

#define HC_SHARED_GET HC_PASTE(HOOKCHAIN_SELF, _mac_shared_instance_get)

namespace
{
struct SharedEntry
{
    uint64_t name;
    std::size_t size;
    void* instance;
};

std::mutex g_sharedLock;
std::vector<SharedEntry> g_shared;

using PeerShared = bool (*)(uint64_t, std::size_t, void**);
const char* const kSharedPeers[] = {"codeware_mac_shared_instance_get", "archivexl_mac_shared_instance_get"};

void* FindLocal(uint64_t aName, std::size_t aSize)
{
    std::scoped_lock lock(g_sharedLock);
    for (const auto& entry : g_shared)
    {
        if (entry.name == aName)
        {
            return entry.size == aSize ? entry.instance : nullptr;
        }
    }
    return nullptr;
}
}

extern "C" __attribute__((visibility("default"))) bool HC_SHARED_GET(uint64_t aName, std::size_t aSize, void** aOut)
{
    void* instance = FindLocal(aName, aSize);
    if (aOut)
    {
        *aOut = instance;
    }
    return instance != nullptr;
}

void* Mac::Shared::Acquire(uint64_t aName, std::size_t aSize)
{
    if (void* local = FindLocal(aName, aSize))
    {
        return local;
    }
    const std::string self = HC_STR(HC_SHARED_GET);
    for (const char* peer : kSharedPeers)
    {
        if (self == peer)
        {
            continue;
        }
        if (auto fn = reinterpret_cast<PeerShared>(dlsym(RTLD_DEFAULT, peer)))
        {
            void* instance = nullptr;
            if (fn(aName, aSize, &instance) && instance)
            {
                MAC_DIAG("[shared] %s uses the instance %#llx of %s (%p)\n", HC_STR(HOOKCHAIN_SELF),
                             static_cast<unsigned long long>(aName), peer, instance);
                return instance;
            }
        }
    }
    return nullptr;
}

void Mac::Shared::Publish(uint64_t aName, std::size_t aSize, void* aInstance)
{
    std::scoped_lock lock(g_sharedLock);
    g_shared.push_back({aName, aSize, aInstance});
}
