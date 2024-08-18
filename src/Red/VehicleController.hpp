#pragma once

namespace Raw::VehicleController
{
constexpr auto ToggleAuxLights = Core::RawFunc<
    /* addr = */ Red::AddressLib::VehicleController_ToggleAuxLights,
    /* type = */ void (*)(Red::vehicleController* aController, bool aEnable, Red::vehicleELightType aLightType)>();
}
