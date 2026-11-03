// SELFTEST R17. Self-tests for the Part B changes of R17 (trap stubs, full registration, app structure).
// Runs only with CODEWARE_MAC_DIAG=1, at the start of codeware_postLoadScripts.

#include "MacR13.hpp"

#include "MacDiag.hpp"
#include "MacTrap.hpp"

#include "Red/Scripting.hpp"

#include <RED4ext/Relocation.hpp>

#include <cstdio>

namespace
{
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
            MAC_DIAG( "[selftest] R17 FAIL %s\n", aWhat);
        }
    }
};

// B1. Two known-unmapped addresses, called the two ways Codeware reaches the game:
//   a Codeware Core::RawFunc (CBaseStack_ResolveContext, 1745688837, declared but used by nothing, so it stays a trap) and an
//   SDK hash resolved by the SDK's own resolver (ResourceToken_dtor, 2589919757, unused). R17 used ISerializable_Clone and
//   CEnum_ToString; R19 mapped both, so the test moved to hashes that no code reaches. Each must resolve to a trap, log "[cw] not on Mac yet: <name>" once on its call,
//   return zero, and the game must go on.
void TrapSelfTest(Tally& aTally)
{
    const unsigned hitsBefore = Mac::TrapHitCount();

    Red::Handle<Red::ISerializable> in;
    Red::Handle<Red::ISerializable> out;
    constexpr auto unusedRaw = Core::RawFunc<
        /* addr = */ Red::AddressLib::CBaseStack_ResolveContext,
        /* type = */ void* (*)(Red::Handle<Red::ISerializable>&, const Red::Handle<Red::ISerializable>&)>();
    void* rawResult = unusedRaw(out, in);
    aTally.Check(rawResult == nullptr, "RawFunc trap returns 0");
    aTally.Check(!out, "RawFunc trap leaves the output handle empty");

    const uintptr_t sdkAddress = RED4ext::UniversalRelocBase::Resolve(2589919757u);
    aTally.Check(sdkAddress != 0, "SDK resolver returns a stub for an unmapped hash");
    aTally.Check(Mac::IsTrapAddress(sdkAddress), "the SDK address is a trap stub");
    using Fn = uint64_t (*)(void*, void*);
    const uint64_t sdkResult = reinterpret_cast<Fn>(sdkAddress)(nullptr, nullptr);
    aTally.Check(sdkResult == 0, "SDK trap returns 0");

    const unsigned hitsAfter = Mac::TrapHitCount();
    aTally.Check(hitsAfter >= hitsBefore + 2, "two traps fired");
    // Calling the same traps again must not log again and must still return zero.
    aTally.Check(unusedRaw(out, in) == nullptr, "second call returns 0");
    aTally.Check(Mac::TrapHitCount() == hitsAfter, "a trap logs only once");

    // A float-returning unmapped function (IRenderProxy_sub_60, 3491501770): the trap must hand back 0.0, not the
    // argument that was in s0 on entry.
    const uintptr_t fltAddress = RED4ext::UniversalRelocBase::Resolve(3491501770u);
    aTally.Check(Mac::IsTrapAddress(fltAddress), "the float function resolves to a trap");
    using FltFn = float (*)(float);
    const float fltResult = reinterpret_cast<FltFn>(fltAddress)(7.0f);
    aTally.Check(fltResult == 0.0f, "float trap returns 0.0");

    // A data hash (LaunchParameters, 677908004) resolves to a zeroed buffer.
    const uintptr_t dataAddress = RED4ext::UniversalRelocBase::Resolve(677908004u);
    aTally.Check(dataAddress != 0 && Mac::IsTrapAddress(dataAddress), "a data hash resolves to the trap buffer");
    aTally.Check(dataAddress != 0 && *reinterpret_cast<const double*>(dataAddress) == 0.0, "the trap buffer reads as zero");

    MAC_DIAG( "[selftest] R17 trap: table %u hashes, fired %u -> %u, rawResult=%p sdkResult=%llu\n",
                 Mac::TrapTableSize(), hitsBefore, hitsAfter, rawResult, static_cast<unsigned long long>(sdkResult));
}
}

void Mac::R17SelfTest()
{
    if (!Mac::DiagEnabled())
    {
        return;
    }

    Tally tally;
    TrapSelfTest(tally);
    MAC_DIAG( "[selftest] R17 %s (checks=%d failed=%d)\n", tally.failed == 0 ? "PASS" : "FAIL", tally.checks,
                 tally.failed);
    std::fflush(stderr);
}

// DIAG R17. After the script types register: every RTTI property whose type did not resolve (a null type crashes the
// game's validator), and whether the district enum behind OpenWorldActivityRequest.districts exists yet.
void Mac::R17AuditPropertyTypes(const char* aWhen)
{
    if (!Mac::DiagEnabled())
    {
        return;
    }
    auto* rtti = RED4ext::CRTTISystem::Get();
    if (!rtti)
    {
        return;
    }
    RED4ext::DynArray<RED4ext::CClass*> classes;
    rtti->GetClasses(nullptr, classes);
    unsigned withoutType = 0;
    unsigned shown = 0;
    unsigned props = 0;
    for (auto* cls : classes)
    {
        if (!cls)
        {
            continue;
        }
        for (uint32_t i = 0; i < cls->props.Size(); ++i)
        {
            auto* prop = cls->props[i];
            ++props;
            if (prop && !prop->type)
            {
                ++withoutType;
                if (shown < 60)
                {
                    ++shown;
                    MAC_DIAG( "[diag] R17 audit %s: %s.%s has no type\n", aWhen, cls->name.ToString(),
                                 prop->name.ToString());
                }
            }
        }
    }
    MAC_DIAG( "[diag] R17 audit %s: %u classes, %u properties, %u without a type\n", aWhen,
                 static_cast<unsigned>(classes.Size()), props, withoutType);
    constexpr auto districtName = Red::GetTypeName<Red::gamedataDistrict>();
    MAC_DIAG( "[diag] R17 audit %s: enum gamedataDistrict=%p type array:gamedataDistrict=%p resolved name=%s Red::GetType=%p\n",
                 aWhen, static_cast<void*>(rtti->GetEnum(RED4ext::CName("gamedataDistrict"))),
                 static_cast<void*>(rtti->GetType(RED4ext::CName("array:gamedataDistrict"))), districtName.ToString(),
                 static_cast<void*>(Red::GetType<Red::gamedataDistrict>()));
}
