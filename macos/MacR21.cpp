// SELFTEST R21. See MacR21.hpp.

#include "MacR21.hpp"

#include "MacDiag.hpp"
#include "MacAddressResolver.hpp"
#include "MacEngine.hpp"

#include "Red/CommunitySystem.hpp"
#include "Red/RuntimeScene.hpp"
#include "Red/TagSystem.hpp"

#include <atomic>
#include <cstring>
#include <cstdio>
#include <string>
#include <utility>

namespace
{
std::atomic<int> s_checks{0};
std::atomic<int> s_failed{0};
}

void Mac::R21Check(bool aOk, const char* aWhat)
{
    s_checks.fetch_add(1);
    if (!aOk)
    {
        s_failed.fetch_add(1);
        MAC_DIAG( "[selftest] R21 FAIL %s\n", aWhat);
    }
}

void Mac::R21Summary(const char* aWhen)
{
    if (!Mac::DiagEnabled())
        return;
    const int failed = s_failed.load();
    MAC_DIAG( "[selftest] R21 %s@%s (checks=%d failed=%d)\n", failed == 0 ? "PASS" : "FAIL", aWhen, s_checks.load(), failed);
}

// The SDK SharedSpinLock against the game's own lock functions, on a local byte (nothing of the game is touched): the Mac protocol is bit 7
// for a writer and low bits for readers. 0x20E8 is the game's try-exclusive (0 -> 0x80), 0x2100 its try-shared (add 1 when bit 7 is clear).
static void R21LockProtocolTest()
{
    using TryFn = uint32_t (*)(volatile char*);
    const auto base = Red::MacGameBase();
    auto gameTryExclusive = reinterpret_cast<TryFn>(base + 0x1614);
    auto gameTryShared = reinterpret_cast<TryFn>(base + 0x162C);

    Red::SharedSpinLock lock;
    // An SDK writer: the game must see it as held.
    lock.Lock();
    Mac::R21Check(static_cast<uint8_t>(lock.state) == 0x80, "SDK SharedSpinLock::Lock sets bit 7");
    Mac::R21Check((gameTryExclusive(&lock.state) & 1) == 0, "the game cannot take a lock the SDK holds exclusively");
    Mac::R21Check((gameTryShared(&lock.state) & 1) == 0, "the game cannot share a lock the SDK holds exclusively");
    lock.Unlock();
    Mac::R21Check(lock.state == 0, "SDK SharedSpinLock::Unlock leaves a free lock");
    // An SDK reader: the game must not take it exclusively, and may share it.
    lock.LockShared();
    Mac::R21Check(lock.state == 1, "SDK SharedSpinLock::LockShared adds one reader");
    Mac::R21Check((gameTryExclusive(&lock.state) & 1) == 0, "the game cannot take exclusively a lock the SDK shares");
    lock.UnlockShared();
    Mac::R21Check(lock.state == 0, "SDK SharedSpinLock::UnlockShared leaves a free lock");
    // A game writer: the SDK must see it as held.
    Mac::R21Check((gameTryExclusive(&lock.state) & 1) == 1, "the game takes a free lock exclusively");
    Mac::R21Check(!lock.TryLock(), "the SDK cannot take a lock the game holds exclusively");
    Mac::R21Check(!lock.TryLockShared(), "the SDK cannot share a lock the game holds exclusively");
    lock.state = 0;
}

void Mac::R21WorldAttachTests(RED4ext::world::RuntimeScene* aScene)
{
    if (!Mac::DiagEnabled())
        return;

    static std::atomic<bool> s_lockTested{false};
    if (!s_lockTested.exchange(true))
        R21LockProtocolTest();

    if (!aScene)
        return;

    // Weather: the scene holds the weather system handle at +0x280 (same offset as Windows); the two getters return their Handle
    // through x8 on Mac. Read-only.
    auto& weatherHandle = Raw::RuntimeScene::Weather::Ref(aScene);
    auto* weather = weatherHandle.instance;
    MAC_DIAG( "[selftest] R21 weather system=%p (%s)\n", static_cast<void*>(weather),
                 weather && weather->GetType() ? weather->GetType()->name.ToString() : "-");
    if (weather)
    {
        Red::Handle<Red::worldEnvironmentDefinition> definition;
        Raw::RuntimeSystemWeather::GetEnvironmentDefinition(weather, definition);
        Red::Handle<Red::worldWeatherState> state;
        Raw::RuntimeSystemWeather::GetWeatherState(weather, state);

        static auto* definitionType = Red::GetClass("worldEnvironmentDefinition");
        static auto* stateType = Red::GetClass("worldWeatherState");
        const bool definitionOk = definition && definition->GetType() && definitionType && definition->GetType()->IsA(definitionType);
        const bool stateOk = state && state->GetType() && stateType && state->GetType()->IsA(stateType);
        MAC_DIAG( "[selftest] R21 weather: definition=%p (%s) state=%p (%s) cycle=%d stateIndex=%u previous=%u\n",
                     static_cast<void*>(definition.instance), definition && definition->GetType() ? definition->GetType()->name.ToString() : "-",
                     static_cast<void*>(state.instance), state && state->GetType() ? state->GetType()->name.ToString() : "-",
                     Raw::RuntimeSystemWeather::CycleWeather::Ref(weather) ? 1 : 0,
                     Raw::RuntimeSystemWeather::CurrentStateIndex::Ref(weather), Raw::RuntimeSystemWeather::PreviouseStateIndex::Ref(weather));
        // The menu scene may have no weather running yet (both Handles empty is a valid answer); when an object comes back it must be
        // of the right class.
        Mac::R21Check(!definition || definitionOk, "GetEnvironmentDefinition returns a worldEnvironmentDefinition or nothing");
        Mac::R21Check(!state || stateOk, "GetWeatherState returns a worldWeatherState or nothing");
    }

    // Community system: the exact production call (Codeware calls Update(system, true) after every change it queues); with nothing of
    // ours queued it is a pass over the game's own queues.
    if (auto* community = Red::GetGameSystem<Red::gameICommunitySystem>())
    {
        Raw::CommunitySystem::Update(community, true);
        MAC_DIAG( "[selftest] R21 community system=%p updated\n", static_cast<void*>(community));
        Mac::R21Check(true, "CommunitySystem::Update returns");
    }
    else
    {
        MAC_DIAG( "[selftest] R21 community system not present at this world attach\n");
    }
}

void Mac::R21TagRoundTrip(void* aTagSystem)
{
    if (!Mac::DiagEnabled())
        return;

    auto* aSystem = static_cast<Red::redTagSystem*>(aTagSystem);
    if (!aSystem)
        return;
    // A test entity id that no entity has and a test tag. Assign then unassign: the tag map gets an entry and loses it again, no
    // listener is registered for the test tag.
    const Red::EntityID entity(0x00DE00C0DE000021ull);
    const Red::CName tag("CodewareMacSelfTestTag");
    Raw::TagSystem::AssignTag(aSystem, entity, tag);
    Raw::TagSystem::UnassignTag(aSystem, entity, tag);
    MAC_DIAG( "[selftest] R21 tag round trip done on %p\n", static_cast<void*>(aSystem));
    Mac::R21Check(true, "TagSystem AssignTag and UnassignTag return");
}

namespace
{
void* g_registrarImpl = nullptr;

template<typename T>
T ReadAt(const void* aBase, size_t aOffset)
{
    T value{};
    std::memcpy(&value, static_cast<const uint8_t*>(aBase) + aOffset, sizeof(T));
    return value;
}

// Mac layout, read from the registrar's append helper (Mac 0x3D902E4, called with x0 = [registrar]): registrar -> impl; impl+0 points to
// the group array of 16 byte records indexed by the entry's first byte (the tick group, or 4 for a bucket entry). A record holds the entry
// data pointer at +0, the capacity at +8 and the count at +0xC. Entries are 0xC0 bytes on 2.5.0 (0x80 on 2.3.1; the ResizeBuffer stride in 0x4D6F884).
const void* GroupsOf(const void* aImpl)
{
    return ReadAt<const void*>(aImpl, 0);
}

void DumpImpl(const void* aImpl, const char* aWhen)
{
    const void* groups = GroupsOf(aImpl);
    if (!groups)
    {
        MAC_DIAG( "[diag] R21 registrar %s impl=%p has no group array\n", aWhen, aImpl);
        return;
    }
    std::string line;
    for (size_t g = 0; g < 5; ++g)
    {
        char buf[24];
        std::snprintf(buf, sizeof(buf), " %u", ReadAt<uint32_t>(groups, g * 16 + 0xC));
        line += buf;
    }
    MAC_DIAG( "[diag] R21 registrar %s impl=%p groups=%p counts of groups 0..4:%s\n", aWhen, aImpl, groups, line.c_str());
}
}

uint32_t Mac::R21RegistrarGroup0Count(void* aRegistrar)
{
    if (!Mac::DiagEnabled() || !aRegistrar)
        return 0;
    const void* impl = ReadAt<const void*>(aRegistrar, 0);
    const void* groups = impl ? GroupsOf(impl) : nullptr;
    return groups ? ReadAt<uint32_t>(groups, 0xC) : 0;
}

void Mac::R21DumpRegistrar(void* aRegistrar, const char* aWhen)
{
    if (!Mac::DiagEnabled() || !aRegistrar)
        return;
    const void* impl = ReadAt<const void*>(aRegistrar, 0);
    if (!impl)
        return;
    g_registrarImpl = const_cast<void*>(impl);
    DumpImpl(impl, aWhen);
}

void Mac::R21CheckRegistration(void* aRegistrar, uint32_t aCountBefore, const char* aName, void* aSystem)
{
    // The entry layout is the game's own (read from UpdateRegistrar_RegisterGroupUpdate, Mac 0x3D95800): byte 0 = group, a 0x20 byte
    // callback buffer at +8, the callback handler at +0x48, the system's CClass* at +0x98, the name at +0xA0, the live argument 0xA at +0xA8 (Mac 2.5.0; 2.3.1: +0x28/+0x58/+0x60/+0x68, and the 0x20 byte buffer at +8 became 0x40).
    if (!Mac::DiagEnabled() || !aRegistrar)
        return;
    const void* impl = ReadAt<const void*>(aRegistrar, 0);
    const void* groups = impl ? GroupsOf(impl) : nullptr;
    if (!groups)
    {
        Mac::R21Check(false, "the update registrar has a group array");
        return;
    }
    const uint32_t count = ReadAt<uint32_t>(groups, 0xC);
    Mac::R21Check(count == aCountBefore + 1, "UpdateRegistrar_RegisterGroupUpdate appended one FrameBegin entry");
    const auto* data = ReadAt<const uint8_t*>(groups, 0);
    if (!data || count == 0)
        return;
    const uint8_t* entry = data + static_cast<size_t>(count - 1) * 0xC0; // 2.5.0 entry size (2.3.1: 0x80)
    const char* name = ReadAt<const char*>(entry, 0xA0);
    Mac::R21Check(ReadAt<uint8_t>(entry, 0) == 0, "the appended entry is in group 0 (FrameBegin)");
    Mac::R21Check(ReadAt<uint64_t>(entry, 0x48) != 0, "the appended entry has a callback handler");
    Mac::R21Check(name && std::strcmp(name, aName) == 0, "the appended entry carries the system's tick name");
    Mac::R21Check(ReadAt<uint32_t>(entry, 0xA8) == 0xA, "the appended entry carries the live argument 0xA");
    Mac::R21Check(ReadAt<uint64_t>(entry, 0x98) != 0, "the appended entry carries the system's class");
    // The first word of the callback buffer is the system the member function is bound to.
    Mac::R21Check(ReadAt<uint64_t>(entry, 0x8) == reinterpret_cast<uint64_t>(aSystem), "the callback is bound to the system");
}

void Mac::R21CheckAtT50()
{
    if (!Mac::DiagEnabled())
        return;
    if (g_registrarImpl)
        DumpImpl(g_registrarImpl, "@t+50s");
    static const char* kNames[] = {"StaticEntitySystem_RegisterUpdates", "StaticEntitySystem_Tick", "PersistentObject_InitializeState", "PointOfInterestMappin_SetPhase"};
    std::string line;
    for (const char* name : kNames)
    {
        char buf[96];
        std::snprintf(buf, sizeof(buf), " %s=%llu", name, static_cast<unsigned long long>(Mac::HookCount(name).calls.load()));
        line += buf;
    }
    MAC_DIAG( "[selftest] R21 counters@t+50s%s\n", line.c_str());
    // The registration itself is checked at the call (R21CheckRegistration). Whether the game's scheduler runs group 0 at the menu is
    // not known: the game's own FrameBegin entries are world runtime systems (RuntimeSystemNodeStreaming and others) that tick with a
    // loaded world. So a zero here is reported, not failed; the in-game test (INGAME_TESTS.md) is the real check.
    const auto ticks = Mac::HookCount("StaticEntitySystem_Tick").calls.load();
    MAC_DIAG( "[selftest] R21 StaticEntitySystem tick calls at the menu: %llu (%s)\n", static_cast<unsigned long long>(ticks),
                 ticks ? "the game's scheduler runs group 0" : "none at the menu, checked in game");
}
