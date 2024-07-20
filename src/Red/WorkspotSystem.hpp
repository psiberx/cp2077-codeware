#pragma once

namespace Raw::workWorkspotSystem
{
using SpinLock = Core::OffsetPtr<0x50, Red::SharedSpinLock>;
using InstanceMap = Core::OffsetPtr<0x70, Red::HashMap<uint64_t, Red::workWorkspotInstance*>>;

constexpr auto GetWorkspotInstance = Core::RawFunc<
    /* addr = */ Red::AddressLib::WorkspotSystem_GetWorkspotInstance,
    /* type = */ Red::workWorkspotInstance* (*)(Red::workWorkspotSystem* aSystem, const Red::EntityID& aEntityID)>();
}
