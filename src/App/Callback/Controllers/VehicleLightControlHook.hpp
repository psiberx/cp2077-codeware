#pragma once

#include "App/Callback/CallbackSystem.hpp"
#include "App/Callback/CallbackSystemController.hpp"
#include "App/Callback/Events/VehicleLightControlEvent.hpp"
#include "Core/Hooking/HookingAgent.hpp"
#include "Red/VehicleController.hpp"

namespace App
{
class VehicleLightControlHook
    : public CallbackSystemController
    , public Core::HookingAgent
{
public:
    constexpr static auto EventName = Red::CName("Vehicle/ToggleAuxLights");

    Core::Map<Red::CName, Red::CName> GetEvents() override
    {
        return {{EventName, Red::GetTypeName<VehicleLightControlEvent>()}};
    }

protected:
    bool OnActivateHook() override
    {
        return IsHooked<Raw::VehicleController::ToggleAuxLights>() || HookAfter<Raw::VehicleController::ToggleAuxLights>(&OnToggleLights);
    }

    bool OnDeactivateHook() override
    {
        return !IsHooked<Raw::VehicleController::ToggleAuxLights>() || Unhook<Raw::VehicleController::ToggleAuxLights>();
    }

    inline static void OnToggleLights(Red::vehicleController* aController, bool aEnable, Red::vehicleELightType aLightType)
    {
        auto vehicleEntity = Red::AsWeakHandle(aController->owner);
        if (vehicleEntity)
        {
            CallbackSystem::Get()->DispatchNativeEvent<VehicleLightControlEvent>(EventName, vehicleEntity, aEnable, aLightType);
        }
    }
};
}
