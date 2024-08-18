#pragma once

namespace Raw::VehicleController
{
constexpr auto ToggleLights = Core::RawFunc<
    /* addr = */ Red::AddressLib::VehicleController_ToggleLights,
    /* type = */ void (*)(Red::vehicleController* aController, bool aEnable, Red::vehicleELightType aLightType)>();
}
