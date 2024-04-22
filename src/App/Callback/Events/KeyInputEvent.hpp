#pragma once

#include "App/Callback/CallbackSystemEvent.hpp"
#include "Red/Input.hpp"

namespace App
{
struct KeyInputEvent : CallbackSystemEvent
{
    KeyInputEvent()
        : CallbackSystemEvent()
        , state()
        , action(Red::EInputAction::IACT_None)
        , key(Red::EInputKey::IK_None)
    {
    }

    KeyInputEvent(Red::CName aName, Red::KeyboardState& aState, const Red::RawInputData& aInput)
        : CallbackSystemEvent(aName)
        , state(aState)
        , action(aInput.action)
        , key(aInput.key)
    {
    }

    KeyInputEvent(Red::CName aName, Red::KeyboardState& aState, Red::EInputAction aAction, Red::EInputKey aKey)
        : CallbackSystemEvent(aName)
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
    RTTI_PARENT(App::CallbackSystemEvent);
    RTTI_METHOD(IsShiftDown);
    RTTI_METHOD(IsControlDown);
    RTTI_METHOD(IsAltDown);
    RTTI_GETTER(action);
    RTTI_GETTER(key);
});
