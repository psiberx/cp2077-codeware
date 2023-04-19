#pragma once

#include "App/Scripting/CallbackSystem.hpp"
#include "App/Scripting/EventController.hpp"
#include "App/UI/WidgetInputService.hpp"
#include "Core/Facades/Container.hpp"
#include "KeyInputEvent.hpp"

namespace App
{
class RawInputHandler : public EventController
{
public:
    constexpr static auto KeyEventName = Red::CName("Input/Key");
    constexpr static auto AxisEventName = Red::CName("Input/Axis");

    Core::Vector<Red::CName> GetEvents() override
    {
        return {KeyEventName};
    }

    bool Initialize() override
    {
        Core::Resolve<WidgetInputService>()->SetCallback(&OnInput);
        return true;
    }

    bool Uninitialize() override
    {
        Core::Resolve<WidgetInputService>()->ClearCallback();
        return true;
    }

protected:
    inline static void OnInput(Red::KeyboardState& aState, Red::EInputAction aAction, Red::EInputKey aKey)
    {
        if (aAction != Red::EInputAction::IACT_Axis)
        {
            CallbackSystem::PassEvent<KeyInputEvent>(KeyEventName, aState, aAction, aKey);
        }
    }
};
}
