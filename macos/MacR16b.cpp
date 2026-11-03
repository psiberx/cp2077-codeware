// SELFTEST R16b. Checks the vtables of the game systems against Codeware's own systems, then calls the
// IsSavingLocked slot the way the game does, once at the first world attach (menu, no save).
//
// Why it exists: the third Phase 6 session crashed on the first autosave, at a fast travel. The game collects
// the save locks with GameInstance::<0x3314DDC>: for each system in GameInstance.systemInstances it calls vtable
// slot 0x178 as IsSavingLocked(this = x0, bool = x1) with the SaveLock returned through x8 (AArch64 indirect
// result register). The SDK declares it as void* IsSavingLocked(SaveLock* aLock, bool a2), so Codeware's systems
// treated the bool as the SaveLock pointer and wrote through null. The fix is in macos/inc/RED4ext/.../
// gameIGameSystem*.hpp. This file proves it without loading a save.
//
// Stage 1 reads memory only (vm_read_overwrite): the vtables of every game system, a table per slot.
// Stage 2 calls slot 0x178 on each Codeware system with the Mac signature and checks the returned SaveLock.
// Stage 3 calls the game's own walker (0x3314DDC), which calls IsSavingLocked on every system including the
//         game's. It is the function frame #3 of the crash was in. It only reads state.

#include "MacDiag.hpp"
#include "MacR13.hpp"
#include "MacR15.hpp"

#include "MacAddressResolver.hpp"

#include <RED4ext/GameEngine.hpp>
#include <RED4ext/Scripting/Natives/Generated/game/SaveLock.hpp>

#include <dlfcn.h>
#include <mach/mach.h>
#include <mach/vm_map.h>

#include <cstdint>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <map>
#include <string>
#include <vector>

namespace Red
{
RED4ext::GameInstance* MacGameInstance();
}

namespace
{
constexpr uintptr_t kWalkerRva = 0x1AE852C;    // GameInstance: collects the save locks (GatherSaveLocks)
constexpr uintptr_t kIsSavingLockedSlot = 0x178; // Mac offset (Windows 0x170, shifted by the second destructor slot)
constexpr uintptr_t kSlotFirst = 0x00;
constexpr uintptr_t kSlotLast = 0x1D0;           // inclusive, covers IScriptable up to a few slots past OnUninitialize

bool SafeRead64(uintptr_t aAddress, uint64_t& aOut)
{
    vm_size_t got = 0;
    return vm_read_overwrite(mach_task_self(), static_cast<vm_address_t>(aAddress), sizeof(aOut),
                             reinterpret_cast<vm_address_t>(&aOut), &got) == KERN_SUCCESS &&
           got == sizeof(aOut);
}

struct System
{
    std::string name;
    uintptr_t object = 0;
    uintptr_t vptr = 0;
    bool codeware = false;
    std::vector<uint64_t> slots; // index = (offset - kSlotFirst) / 8
};

uintptr_t g_gameBase = 0;
uintptr_t g_codewareBase = 0;

// "cw+0x1234" for this plugin, "g+0x1234" for the game image, "<image>+0x1234" for others, "null" or "?0x..".
// The Codeware dylib is mapped right after the game image, so it is checked first.
std::string Where(uint64_t aPointer)
{
    if (aPointer == 0)
    {
        return "null";
    }
    char buf[96];
    Dl_info info{};
    if (dladdr(reinterpret_cast<void*>(aPointer), &info) && info.dli_fbase)
    {
        const auto base = reinterpret_cast<uintptr_t>(info.dli_fbase);
        if (base == g_codewareBase)
        {
            std::snprintf(buf, sizeof(buf), "cw+0x%llx", static_cast<unsigned long long>(aPointer - base));
        }
        else if (base == g_gameBase)
        {
            std::snprintf(buf, sizeof(buf), "g+0x%llx", static_cast<unsigned long long>(aPointer - base));
        }
        else
        {
            const char* name = info.dli_fname ? std::strrchr(info.dli_fname, '/') : nullptr;
            name = name ? name + 1 : (info.dli_fname ? info.dli_fname : "?");
            std::snprintf(buf, sizeof(buf), "%s+0x%llx", name, static_cast<unsigned long long>(aPointer - base));
        }
        return buf;
    }
    std::snprintf(buf, sizeof(buf), "?0x%llx", static_cast<unsigned long long>(aPointer));
    return buf;
}

// Slot names, Mac offsets (the Windows SDK offset plus 8 after the second destructor slot). "fwd" marks the SDK
// default stubs that forward to the game's base implementation through an SDK address hash with no Mac row.
const char* SlotName(uintptr_t aOffset)
{
    switch (aOffset)
    {
    case 0x00: return "ISerializable::GetNativeType";
    case 0x08: return "ISerializable::GetType";
    case 0x10: return "ISerializable::GetAllocator";
    case 0x18: return "~ISerializable (complete)";
    case 0x20: return "~ISerializable (deleting)";
    case 0x28: return "ISerializable::sub_20";
    case 0x30: return "ISerializable::PostLoad";
    case 0x38: return "ISerializable::sub_30 [fwd, hash 114701897]";
    case 0x40: return "ISerializable::sub_38";
    case 0x48: return "ISerializable::sub_40 [fwd, hash 2293436409]";
    case 0x50: return "ISerializable::sub_48";
    case 0x58: return "ISerializable::sub_50";
    case 0x60: return "ISerializable::sub_58";
    case 0x68: return "ISerializable::sub_60";
    case 0x70: return "ISerializable::sub_68";
    case 0x78: return "ISerializable::sub_70";
    case 0x80: return "ISerializable::sub_78 [fwd, hash 2715367827]";
    case 0x88: return "ISerializable::sub_80";
    case 0x90: return "ISerializable::sub_88";
    case 0x98: return "ISerializable::sub_90";
    case 0xa0: return "ISerializable::sub_98";
    case 0xa8: return "ISerializable::sub_A0 [fwd, hash 3978435378]";
    case 0xb0: return "ISerializable::sub_A8";
    case 0xb8: return "ISerializable::sub_B0";
    case 0xc0: return "ISerializable::sub_B8";
    case 0xc8: return "ISerializable::sub_C0 [fwd, hash 2149588021]";
    case 0xd0: return "ISerializable::sub_C8";
    case 0xd8: return "ISerializable::CanBeDestructed";
    case 0xe0: return "IScriptable::sub_D8 [fwd, hash 4175699423]";
    case 0xe8: return "IScriptable::sub_E0";
    case 0xf0: return "IScriptable::sub_E8";
    case 0xf8: return "IScriptable::sub_F0";
    case 0x100: return "IScriptable::sub_F8";
    case 0x108: return "IScriptable::sub_100";
    case 0x110: return "IUpdatableSystem::OnRegisterUpdates";
    case 0x118: return "IGameSystem::OnWorldAttached";
    case 0x120: return "IGameSystem::OnBeforeWorldDetach";
    case 0x128: return "IGameSystem::OnWorldDetached";
    case 0x130: return "IGameSystem::OnAfterWorldDetach";
    case 0x138: return "IGameSystem::OnBeforeGameSave";
    case 0x140: return "IGameSystem::OnGameSave";
    case 0x148: return "IGameSystem::OnAfterGameSave";
    case 0x150: return "IGameSystem::OnGameLoad";
    case 0x158: return "IGameSystem::OnGameRestored";
    case 0x160: return "IGameSystem::OnGamePrepared";
    case 0x168: return "IGameSystem::OnGamePaused";
    case 0x170: return "IGameSystem::OnGameResumed";
    case 0x178: return "IGameSystem::IsSavingLocked (R16b: x8 return)";
    case 0x180: return "IGameSystem::OnStreamingWorldLoaded";
    case 0x188: return "IGameSystem::sub_180";
    case 0x190: return "IGameSystem::sub_188";
    case 0x198: return "IGameSystem::sub_190";
    case 0x1a0: return "IGameSystem::sub_198";
    case 0x1a8: return "IGameSystem::OnInitialize";
    case 0x1b0: return "IGameSystem::OnUninitialize";
    default: return "(past the SDK list)";
    }
}

bool LooksLikeGameCode(uint64_t aPointer)
{
    // __TEXT of the game image is [0, 0x6de0000) from the base; instructions are 4-byte aligned.
    return aPointer >= g_gameBase + 0x1000 && aPointer < g_gameBase + 0x6de0000ull && (aPointer & 3) == 0;
}

void Stage1_Vtables(const std::vector<System>& aSystems)
{
    size_t gameCount = 0;
    size_t cwCount = 0;
    for (const auto& s : aSystems)
    {
        (s.codeware ? cwCount : gameCount)++;
    }
    MAC_DIAG( "[selftest] R16b systems: %zu total, %zu game, %zu Codeware\n", aSystems.size(), gameCount, cwCount);
    for (const auto& s : aSystems)
    {
        if (s.codeware)
        {
            MAC_DIAG( "[selftest] R16b Codeware system %s object=%p vptr=%s\n", s.name.c_str(),
                         reinterpret_cast<void*>(s.object), Where(s.vptr).c_str());
        }
    }

    // How far the game's vtables run: count consecutive code pointers from the IGameSystem range on.
    size_t minEnd = ~size_t{0};
    size_t maxEnd = 0;
    for (const auto& s : aSystems)
    {
        if (s.codeware)
        {
            continue;
        }
        size_t last = 0;
        for (size_t i = 0; i < s.slots.size(); ++i)
        {
            if (!LooksLikeGameCode(s.slots[i]))
            {
                break;
            }
            last = kSlotFirst + i * 8;
        }
        minEnd = std::min(minEnd, last);
        maxEnd = std::max(maxEnd, last);
    }
    MAC_DIAG( "[selftest] R16b game system vtables: consecutive code slots run to 0x%zx..0x%zx (min..max over %zu)\n",
                 minEnd == ~size_t{0} ? 0 : minEnd, maxEnd, gameCount);

    // One line per slot: the game's most common target and how Codeware's systems compare.
    for (size_t i = 0; i < (kSlotLast - kSlotFirst) / 8 + 1; ++i)
    {
        std::map<uint64_t, int> hist;
        int games = 0;
        for (const auto& s : aSystems)
        {
            if (!s.codeware && i < s.slots.size())
            {
                ++hist[s.slots[i]];
                ++games;
            }
        }
        uint64_t mode = 0;
        int modeCount = 0;
        for (const auto& [target, count] : hist)
        {
            if (count > modeCount)
            {
                mode = target;
                modeCount = count;
            }
        }
        // Codeware's systems: one shared target means the SDK default stub, several mean overrides.
        std::map<uint64_t, std::string> cwTargets;
        int cwSystems = 0;
        for (const auto& s : aSystems)
        {
            if (!s.codeware || i >= s.slots.size())
            {
                continue;
            }
            ++cwSystems;
            auto& names = cwTargets[s.slots[i]];
            names += names.empty() ? "" : ",";
            names += s.name.substr(0, 12);
        }
        std::string cw;
        if (cwTargets.size() == 1 && cwSystems > 1)
        {
            cw = " shared " + Where(cwTargets.begin()->first) + " (" + std::to_string(cwSystems) + " systems)";
        }
        else
        {
            for (const auto& [target, names] : cwTargets)
            {
                cw += " " + names + "=" + Where(target);
            }
        }
        MAC_DIAG( "[selftest] R16b slot 0x%03zx %-44s game %s (%d/%d, %zu distinct) | codeware%s\n",
                     kSlotFirst + i * 8, SlotName(kSlotFirst + i * 8), Where(mode).c_str(), modeCount, games, hist.size(),
                     cw.c_str());
    }
}

bool Stage2_IsSavingLocked(const std::vector<System>& aSystems)
{
    bool ok = true;
    for (const auto& s : aSystems)
    {
        if (!s.codeware)
        {
            continue;
        }
        const auto index = (kIsSavingLockedSlot - kSlotFirst) / 8;
        if (index >= s.slots.size() || s.slots[index] == 0)
        {
            MAC_DIAG( "[selftest] R16b FAIL %s: slot 0x178 is empty\n", s.name.c_str());
            ok = false;
            continue;
        }
        // The Mac signature: SaveLock returned by value (x8), this in x0, bool in x1. This is the call the game makes.
        using Fn = RED4ext::game::SaveLock (*)(void*, bool);
        const auto fn = reinterpret_cast<Fn>(s.slots[index]);
        for (const bool flag : {false, true})
        {
            RED4ext::game::SaveLock lock = fn(reinterpret_cast<void*>(s.object), flag);
            const bool good = lock.reason == RED4ext::game::SaveLockReason::Nothing && lock.description.Length() == 0;
            MAC_DIAG( "[selftest] R16b %s IsSavingLocked(%d) -> reason=%d description length=%u %s\n", s.name.c_str(),
                         flag ? 1 : 0, static_cast<int>(lock.reason), lock.description.Length(), good ? "ok" : "UNEXPECTED");
            ok = ok && good;
        }
    }
    return ok;
}

void Stage3_Walker(RED4ext::GameInstance* aGame)
{
    using Walker = void (*)(void*, RED4ext::DynArray<RED4ext::game::SaveLock>*, bool);
    const auto walker = reinterpret_cast<Walker>(g_gameBase + kWalkerRva);
    RED4ext::DynArray<RED4ext::game::SaveLock> locks;
    MAC_DIAG( "[selftest] R16b calling the game's save-lock collector g+0x%lx (GameInstance=%p)\n",
                 static_cast<unsigned long>(kWalkerRva), static_cast<void*>(aGame));
    std::fflush(stderr);
    walker(aGame, &locks, false);
    MAC_DIAG( "[selftest] R16b save-lock collector returned: %u lock(s)\n", locks.Size());
    for (uint32_t i = 0; i < locks.Size() && i < 8; ++i)
    {
        MAC_DIAG( "[selftest] R16b   lock %u: reason=%d description=\"%s\"\n", i, static_cast<int>(locks[i].reason),
                     locks[i].description.c_str());
    }
}
}

void Mac::R16bSelfTest()
{
    if (!Mac::DiagEnabled())
    {
        return;
    }
    static bool s_done = false;
    if (s_done)
    {
        return;
    }
    s_done = true;

    g_gameBase = Red::MacGameBase();
    {
        Dl_info info{};
        dladdr(reinterpret_cast<void*>(&Mac::R16bSelfTest), &info);
        g_codewareBase = reinterpret_cast<uintptr_t>(info.dli_fbase);
    }

    auto* game = Red::MacGameInstance();
    if (!game)
    {
        MAC_DIAG( "[selftest] R16b FAIL no GameInstance\n");
        return;
    }

    std::vector<System> systems;
    for (uint32_t i = 0; i < game->systemInstances.Size(); ++i)
    {
        auto* object = game->systemInstances[i].instance;
        if (!object)
        {
            continue;
        }
        System s;
        s.object = reinterpret_cast<uintptr_t>(object);
        uint64_t vptr = 0;
        if (!SafeRead64(s.object, vptr) || vptr == 0)
        {
            continue;
        }
        s.vptr = static_cast<uintptr_t>(vptr);
        Dl_info info{};
        s.codeware = dladdr(reinterpret_cast<void*>(s.vptr), &info) && reinterpret_cast<uintptr_t>(info.dli_fbase) == g_codewareBase;
        auto* type = object->GetType();
        s.name = type ? type->name.ToString() : "?";
        for (uintptr_t off = kSlotFirst; off <= kSlotLast; off += 8)
        {
            uint64_t value = 0;
            s.slots.push_back(SafeRead64(s.vptr + off, value) ? value : 0);
        }
        systems.push_back(std::move(s));
    }

    Stage1_Vtables(systems);
    std::fflush(stderr);

    const bool saveLockOk = Stage2_IsSavingLocked(systems);
    MAC_DIAG( "[selftest] R16b IsSavingLocked on Codeware systems %s\n", saveLockOk ? "PASS" : "FAIL");
    std::fflush(stderr);

    Stage3_Walker(game);
    MAC_DIAG( "[selftest] R16b PASS=%d (Codeware IsSavingLocked ok, game collector returned)\n", saveLockOk ? 1 : 0);
    std::fflush(stderr);
}
