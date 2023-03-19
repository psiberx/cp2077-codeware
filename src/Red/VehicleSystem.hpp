#pragma once

#include "Addresses.hpp"

namespace Raw::VehicleSystem
{
constexpr auto ToggleGarageVehicle = Core::RawFunc<
    /* addr = */ Red::Addresses::VehicleSystem_ToggleGarageVehicle,
    /* type = */ bool (*)(Red::VehicleSystem* aSystem, const Red::GarageVehicleID& aVehicleID, bool aEnable)>();
}
