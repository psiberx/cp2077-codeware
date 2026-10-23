#pragma once

namespace Raw::workWorkspotSystem
{
// Game 2.5: 0x5DBBA8 `lea rdx,[rcx+0x50]` (lock) before GetWorkspotInstance, which does `add rcx,0x70` (0x5DBBF7).
using SpinLock = Core::OffsetPtr<0x50, Red::SharedSpinLock>;
using InstanceMap = Core::OffsetPtr<0x70, Red::HashMap<uint64_t, Red::workWorkspotInstance*>>;

constexpr auto GetWorkspotInstance = Core::RawFunc<
    /* addr = */ Red::AddressLib::WorkspotSystem_GetWorkspotInstance,
    /* type = */ Red::workWorkspotInstance* (*)(Red::workWorkspotSystem* aSystem, const Red::EntityID& aEntityID)>();
}
