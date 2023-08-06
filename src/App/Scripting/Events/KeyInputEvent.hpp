#pragma once

#include "App/Scripting/EventObject.hpp"
#include "Red/Input.hpp"

namespace App
{
struct KeyInputEvent : NamedEvent
{
    KeyInputEvent()
        : NamedEvent()
        , state()
        , action(Red::EInputAction::IACT_None)
        , key(Red::EInputKey::IK_None)
    {
    }

    KeyInputEvent(Red::CName aName, Red::KeyboardState& aState, const Red::RawInputData& aInput)
        : NamedEvent(aName)
        , state(aState)
        , action(aInput.action)
        , key(aInput.key)
    {
    }

    KeyInputEvent(Red::CName aName, Red::KeyboardState& aState, Red::EInputAction aAction, Red::EInputKey aKey)
        : NamedEvent(aName)
        , state(aState)
        , action(aAction)
        , key(aKey)
    {
    }

    [[nodiscard]] bool IsShiftDown() const
    {
        return state.shiftLeft || state.shiftRight;
    }

    [[nodiscard]] bool IsControlDown() const
    {
        return state.controlLeft || state.controlRight;
    }

    [[nodiscard]] bool IsAltDown() const
    {
        return state.altLeft || state.altRight;
    }

    Red::KeyboardState state;
    Red::EInputAction action;
    Red::EInputKey key;

    RTTI_IMPL_TYPEINFO(KeyInputEvent);
    RTTI_IMPL_ALLOCATOR();
};
}

RTTI_DEFINE_CLASS(App::KeyInputEvent, {
    RTTI_PARENT(App::NamedEvent);
    RTTI_METHOD(IsShiftDown);
    RTTI_METHOD(IsControlDown);
    RTTI_METHOD(IsAltDown);
    RTTI_GETTER(action);
    RTTI_GETTER(key);
});
