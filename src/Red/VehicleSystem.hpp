#pragma once

namespace Raw::VehicleSystem
{
constexpr auto ToggleGarageVehicle = Core::RawFunc<
    /* addr = */ Red::AddressLib::VehicleSystem_ToggleGarageVehicle,
    /* type = */ bool (*)(Red::VehicleSystem* aSystem, const Red::GarageVehicleID& aVehicleID, bool aEnable)>();
}
