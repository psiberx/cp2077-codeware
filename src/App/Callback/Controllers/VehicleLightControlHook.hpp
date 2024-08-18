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
    constexpr static auto EventName = Red::CName("Vehicle/ToggleLights");

    Core::Map<Red::CName, Red::CName> GetEvents() override
    {
        return {{EventName, Red::GetTypeName<VehicleLightControlEvent>()}};
    }

protected:
    bool OnActivateHook() override
    {
        return IsHooked<Raw::VehicleController::ToggleLights>() || HookAfter<Raw::VehicleController::ToggleLights>(&OnToggleLights);
    }

    bool OnDeactivateHook() override
    {
        return !IsHooked<Raw::VehicleController::ToggleLights>() || Unhook<Raw::VehicleController::ToggleLights>();
    }

    inline static void OnToggleLights(Red::vehicleController* aController, bool aEnable, Red::vehicleELightType aLightType)
    {
        CallbackSystem::Get()->DispatchNativeEvent<VehicleLightControlEvent>(EventName, Red::AsWeakHandle(aController->owner), aEnable, aLightType);
    }
};
}
