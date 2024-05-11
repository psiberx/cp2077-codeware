#pragma once

#include "App/Callback/CallbackSystem.hpp"
#include "App/Callback/CallbackSystemController.hpp"
#include "App/Callback/Events/AxisInputEvent.hpp"
#include "App/Callback/Events/KeyInputEvent.hpp"
#include "App/UI/WidgetInputService.hpp"
#include "Core/Facades/Container.hpp"
#include "Red/InkSystem.hpp"

namespace App
{
class RawInputHook
    : public CallbackSystemController
    , public Core::HookingAgent
{
public:
    constexpr static auto KeyEventName = Red::CName("Input/Key");
    constexpr static auto AxisEventName = Red::CName("Input/Axis");

    Core::Map<Red::CName, Red::CName> GetEvents() override
    {
        return {
            {KeyEventName, Red::GetTypeName<KeyInputEvent>()},
            {AxisEventName, Red::GetTypeName<AxisInputEvent>()},
        };
    }

protected:
    bool OnActivateHook() override
    {
        return HookBefore<Raw::inkSystem::ProcessInputEvents>(&OnRawInput);
    }

    bool OnDeactivateHook() override
    {
        return Unhook<Raw::inkSystem::ProcessInputEvents>();
    }

    void OnActivateEvent(Red::CName aEvent) override
    {
        if (aEvent == KeyEventName)
        {
            s_isKeyInputActive = true;
        }
        else if (aEvent == AxisEventName)
        {
            s_isAxisInputActive = true;
        }
    }

    void OnDeactivateEvent(Red::CName aEvent) override
    {
        if (aEvent == KeyEventName)
        {
            s_isKeyInputActive = false;
        }
        else if (aEvent == AxisEventName)
        {
            s_isAxisInputActive = false;
        }
    }

    inline static void OnRawInput(Red::InkSystem* aSystem, uint64_t a2, Red::RawInputBuffer& aBuffer)
    {
        if (aSystem->layerManagers.size && aBuffer.inputs.size)
        {
            for (const auto& input : aBuffer.inputs)
            {
                if (input.action != Red::EInputAction::IACT_None && input.key != Red::EInputKey::IK_None)
                {
                    ProcessRawInput(aSystem->keyboardState, input);
                }
            }
        }
    }

    inline static void ProcessRawInput(Red::KeyboardState& aState, const Red::RawInputData& aInput)
    {
        if (aInput.action == Red::EInputAction::IACT_Axis)
        {
            if (s_isKeyInputActive)
            {
                if (aInput.key == Red::EInputKey::IK_Pad_LeftTrigger ||
                    aInput.key == Red::EInputKey::IK_Pad_RightTrigger)
                {
                    if (aInput.value > 0)
                    {
                        if (!s_pressedKeys.contains(aInput.key))
                        {
                            s_pressedKeys.insert(aInput.key);
                            CallbackSystem::Get()->DispatchNativeEvent<KeyInputEvent>(KeyEventName, aState,
                                                                     Red::EInputAction::IACT_Press,
                                                                     aInput.key);
                        }
                    }
                    else
                    {
                        if (s_pressedKeys.contains(aInput.key))
                        {
                            s_pressedKeys.erase(aInput.key);
                            CallbackSystem::Get()->DispatchNativeEvent<KeyInputEvent>(KeyEventName, aState,
                                                                     Red::EInputAction::IACT_Release,
                                                                     aInput.key);
                        }
                    }
                }
            }

            if (s_isAxisInputActive)
            {
                CallbackSystem::Get()->DispatchNativeEvent<AxisInputEvent>(AxisEventName, aState, aInput);
            }
        }
        else
        {
            if (s_isKeyInputActive)
            {
                CallbackSystem::Get()->DispatchNativeEvent<KeyInputEvent>(KeyEventName, aState, aInput);
            }
        }
    }

    inline static Core::Set<Red::EInputKey> s_pressedKeys;
    inline static bool s_isKeyInputActive = false;
    inline static bool s_isAxisInputActive = false;
};
}
