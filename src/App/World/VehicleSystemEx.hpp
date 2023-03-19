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

RTTI_EXPAND_CLASS(App::VehicleSystemEx, Red::VehicleSystem, {
    RTTI_METHOD(ToggleGarageVehicle);
});
