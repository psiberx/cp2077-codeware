#pragma once

#include "Red/VehicleSystem.hpp"

namespace App
{
struct VehicleSystemEx : Red::VehicleSystem
{
    bool ToggleGarageVehicle(const Red::GarageVehicleID& aVehicleID, bool aEnable)
    {
        return Raw::VehicleSystem::ToggleGarageVehicle(this, aVehicleID, aEnable);
    }
};
}

RTTI_EXPAND_CLASS(Red::VehicleSystem, App::VehicleSystemEx, {
    RTTI_METHOD(ToggleGarageVehicle);
});
