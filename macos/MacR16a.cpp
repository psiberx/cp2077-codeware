// SELFTEST R16a. Checks the SDK address rows added in R16a and the property lookup that EntityTarget::Matches
// uses, at postLoadScripts, before any save is loaded. Also holds an env-gated crash trigger used once to measure
// what the crash handler does (inert unless CODEWARE_R16A_CRASHTEST is set).
//
// Why it exists: the first two Phase 6 sessions died in EntityTarget::Matches when a device attached:
// Red::GetPropertyPtr -> CClass::GetProperty -> "[SDK AddressResolver] Unknown hash 0x8f031512" -> call to 0.

#include "MacDiag.hpp"
#include "MacR13.hpp"
#include "MacR15.hpp"

#include "MacAddressResolver.hpp"

#include <RED4ext/Relocation.hpp>

#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <thread>

namespace
{
struct Row
{
    uint32_t hash;
    uintptr_t rva;
    const char* name;
};

// Must equal the rows in MacSdkRows.inc.
constexpr Row kRows[] = {
    {2399343890u, 0x10C4C14, "CClass_GetProperty"},
    {2257327441u, 0x10C37D8, "CClass_InitializeProperties"},
    {2547979664u, 0x10C3934, "CClass_AssignDefaultValuesToProperties"},
};

struct Tally
{
    int checks = 0;
    int failed = 0;

    void Check(bool aOk, const char* aWhat)
    {
        ++checks;
        if (!aOk)
        {
            ++failed;
            MAC_DIAG( "[selftest] R16a FAIL %s\n", aWhat);
        }
    }
};

// Class `aName`: take up to three properties straight from the class's own array and look each one up by name.
void CheckClass(Tally& aTally, const char* aName)
{
    auto* cls = Red::GetClass(Red::CName(aName));
    if (!cls)
    {
        MAC_DIAG( "[selftest] R16a class %s: not in RTTI (skipped)\n", aName);
        return;
    }

    const uint32_t ownCount = cls->props.Size();
    int found = 0;
    for (uint32_t i = 0; i < ownCount && i < 3; ++i)
    {
        auto* prop = cls->props[i];
        if (!prop)
        {
            continue;
        }
        auto* got = cls->GetProperty(prop->name);
        aTally.Check(got == prop, "GetProperty(name of own property) returns that property");
        found += (got == prop) ? 1 : 0;
    }

    // A property of the parent must be found through the parent chain.
    int viaParent = -1;
    for (auto* parent = cls->parent; parent; parent = parent->parent)
    {
        if (parent->props.Size() > 0 && parent->props[0])
        {
            auto* want = parent->props[0];
            auto* got = cls->GetProperty(want->name);
            aTally.Check(got == want, "GetProperty(name of a parent property) walks the parent chain");
            viaParent = (got == want) ? 1 : 0;
            break;
        }
    }

    MAC_DIAG( "[selftest] R16a class %s: size=%u ownProps=%u ownLookups=%d parentChain=%d\n", aName,
                 cls->size, ownCount, found, viaParent);
}

void LogSize(const char* aName, size_t aSdkSize)
{
    if (auto* cls = Red::GetClass(Red::CName(aName)))
    {
        MAC_DIAG( "[selftest] R16a layout %s: RTTI size=%u, SDK sizeof=%zu%s\n", aName, cls->size, aSdkSize,
                     cls->size == aSdkSize ? "" : " (differ)");
    }
}

void CrashTrigger()
{
    const char* when = std::getenv("CODEWARE_R16A_CRASHTEST");
    if (!when || !*when)
    {
        return;
    }
    const int delay = std::atoi(when) > 0 ? std::atoi(when) : 5;
    MAC_DIAG( "[selftest] R16a TEST CRASH armed: a call to a null function in %d s (CODEWARE_R16A_CRASHTEST)\n",
                 delay);
    std::thread([delay] {
        std::this_thread::sleep_for(std::chrono::seconds(delay));
        MAC_DIAG( "[selftest] R16a TEST CRASH now\n");
        std::fflush(stderr);
        volatile auto fn = reinterpret_cast<void (*)()>(static_cast<uintptr_t>(0));
        fn();
    }).detach();
}
}

void Mac::R16aSelfTest()
{
    if (!Mac::DiagEnabled())
    {
        return;
    }
    Tally tally;
    const auto base = Red::MacGameBase();

    // 1. The SDK's own resolver (the one UniversalRelocFunc uses) knows the rows.
    for (const auto& row : kRows)
    {
        const auto resolved = RED4ext::UniversalRelocBase::Resolve(row.hash);
        const bool ok = resolved == base + row.rva;
        MAC_DIAG( "[selftest] R16a resolve %s hash=0x%x -> 0x%lx expected 0x%lx %s\n", row.name, row.hash,
                     static_cast<unsigned long>(resolved - base), static_cast<unsigned long>(row.rva), ok ? "ok" : "MISMATCH");
        tally.Check(ok, "SDK resolver returns the row");
    }

    // 2. The lookup EntityTarget uses: Red::GetPropertyPtr<T>(void* context, CClass*, name), on a plain struct whose
    //    layout we know. Vector4 has the reflected properties X, Y, Z, W.
    {
        Red::Vector4 v{1.0f, 2.0f, 3.0f, 4.0f};
        auto* cls = Red::GetClass(Red::CName("Vector4"));
        tally.Check(cls != nullptr, "Vector4 is in RTTI");
        if (cls)
        {
            auto* prop = cls->GetProperty(Red::CName("Z"));
            tally.Check(prop != nullptr, "CClass::GetProperty(Vector4, Z) is not null");

            auto* z = Red::GetPropertyPtr<float>(&v, cls, Red::CName("Z"));
            auto* w = Red::GetPropertyPtr<float>(&v, cls, Red::CName("W"));
            const bool zOk = z == &v.Z && z && *z == 3.0f;
            const bool wOk = w == &v.W && w && *w == 4.0f;
            tally.Check(zOk, "Red::GetPropertyPtr<float>(Vector4, Z) points at v.Z");
            tally.Check(wOk, "Red::GetPropertyPtr<float>(Vector4, W) points at v.W");
            MAC_DIAG( "[selftest] R16a Vector4: GetProperty(Z)=%p GetPropertyPtr Z=%p (&v.Z=%p, value %.1f) W=%p (&v.W=%p)\n",
                         static_cast<void*>(prop), static_cast<void*>(z), static_cast<void*>(&v.Z), z ? *z : -1.0f,
                         static_cast<void*>(w), static_cast<void*>(&v.W));
            tally.Check(cls->GetProperty(Red::CName("NoSuchProperty_R16a")) == nullptr,
                        "CClass::GetProperty(unknown name) is null");
        }
    }

    // 3. The classes EntityTarget::Matches looks at.
    for (const char* name : {"entEntity", "gameObject", "gameDeviceBase", "gamePuppetBase", "vehicleBaseObject",
                             "gameComponent", "gameDeviceComponentPS", "gamePersistentState"})
    {
        CheckClass(tally, name);
    }
    if (auto* device = Red::GetClass(Red::CName("gameDeviceBase")))
    {
        auto* controller = device->GetProperty(Red::CName("controller"));
        MAC_DIAG( "[selftest] R16a gameDeviceBase.controller: %s\n", controller ? "found" : "NOT found");
    }
    for (const char* psClass : {"gameDeviceComponentPS", "gamePersistentState", "gameComponentPS"})
    {
        if (auto* ps = Red::GetClass(Red::CName(psClass)))
        {
            auto* rec = ps->GetProperty(Red::CName("tweakDBRecord"));
            MAC_DIAG( "[selftest] R16a %s.tweakDBRecord: %s\n", psClass, rec ? "found" : "NOT found");
        }
    }

    // 4. Object layout the record-ID reads depend on (Raw::Puppet::RecordID +0x260, Raw::Vehicle::RecordID +0x658 on 2.5.0, +0x638 on 2.3.1).
    LogSize("entEntity", sizeof(RED4ext::ent::Entity));
    LogSize("gamePuppetBase", sizeof(RED4ext::game::PuppetBase));
    LogSize("vehicleBaseObject", sizeof(RED4ext::vehicle::BaseObject));
    LogSize("gameDeviceBase", sizeof(RED4ext::game::DeviceBase));

    MAC_DIAG( "[selftest] R16a GetProperty %s (checks=%d failed=%d)\n", tally.failed == 0 ? "PASS" : "FAIL",
                 tally.checks, tally.failed);
    std::fflush(stderr);

    CrashTrigger();
}
