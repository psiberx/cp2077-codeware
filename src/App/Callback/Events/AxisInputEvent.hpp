#pragma once

#include "App/Callback/Events/KeyInputEvent.hpp"
#include "Red/Input.hpp"

namespace App
{
struct AxisInputEvent : KeyInputEvent
{
    AxisInputEvent()
        : KeyInputEvent()
        , value(0)
        , mouseX(0)
        , mouseY(0)
    {
    }

    AxisInputEvent(Red::CName aName, Red::KeyboardState& aState, const Red::RawInputData& aInput)
        : KeyInputEvent(aName, aState, aInput)
        , value(aInput.value)
        , mouseX(aInput.mouseX)
        , mouseY(aInput.mouseY)
    {
    }

    float value;
    uint32_t mouseX;
    uint32_t mouseY;

    RTTI_IMPL_TYPEINFO(AxisInputEvent);
    RTTI_IMPL_ALLOCATOR();
};
}

RTTI_DEFINE_CLASS(App::AxisInputEvent, {
    RTTI_PARENT(App::KeyInputEvent);
    RTTI_GETTER(value);
    RTTI_GETTER(mouseX);
    RTTI_GETTER(mouseY);
});
