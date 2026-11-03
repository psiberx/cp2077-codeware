#pragma once

namespace Raw::workWorkspotSystem
{
#if defined(__APPLE__)
// R21: 0x4C and 0x68 on Mac (the base tail padding is reused by the first members). The Mac wrappers lock byte this+0x4C (26 functions in one TU
// call the shared lock after "add x19,x0,#0x4C") and the inlined map find reads buckets [x23,#0x68], size 0x70, modulus 0x74, entries 0x78,
// stride 0x84; the Windows twins use +0x50 and +0x70 (GetWorkspotInstance 0x4F1B00: "add rcx,0x70; call 0x19252C").
using SpinLock = Core::OffsetPtr<0x4C, Red::SharedSpinLock>;
using InstanceMap = Core::OffsetPtr<0x68, Red::HashMap<uint64_t, Red::workWorkspotInstance*>>;
#else
// Game 2.5: 0x5DBBA8 `lea rdx,[rcx+0x50]` (lock) before GetWorkspotInstance, which does `add rcx,0x70` (0x5DBBF7).
using SpinLock = Core::OffsetPtr<0x50, Red::SharedSpinLock>;
using InstanceMap = Core::OffsetPtr<0x70, Red::HashMap<uint64_t, Red::workWorkspotInstance*>>;
#endif

constexpr auto GetWorkspotInstance = Core::RawFunc<
    /* addr = */ Red::AddressLib::WorkspotSystem_GetWorkspotInstance,
    /* type = */ Red::workWorkspotInstance* (*)(Red::workWorkspotSystem* aSystem, const Red::EntityID& aEntityID)>();
}
