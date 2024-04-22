#pragma once

#include "App/Callback/CallbackSystemTarget.hpp"
#include "App/Callback/Events/KeyInputEvent.hpp"

namespace App
{
struct InputTarget : CallbackSystemTarget
{
    InputTarget() = default;

    bool Matches(const Red::Handle<CallbackSystemEvent>& aEvent) override
    {
        const auto* event = aEvent.GetPtr<KeyInputEvent>();

        if (key != Red::EInputKey::IK_None && key != event->key)
            return false;

        if (action != Red::EInputAction::IACT_None && action != event->action)
            return false;

        return true;
    }

    bool Equals(const Red::Handle<CallbackSystemTarget>& aTarget) override
    {
        const auto* target = aTarget.GetPtr<InputTarget>();

        return key == target->key && action == target->action;
    }

    bool Supports(Red::CName aEventType) override
    {
        return aEventType == Red::GetTypeName<KeyInputEvent>();
    }

    static Red::Handle<InputTarget> Key(Red::EInputKey aKey, Red::Optional<Red::EInputAction> aAction)
    {
        auto target = Red::MakeHandle<InputTarget>();
        target->key = aKey;
        target->action = aAction;

        return target;
    }

    static Red::Handle<InputTarget> Axis(Red::EInputKey aAxis, Red::Optional<float> aThreshold)
    {
        auto target = Red::MakeHandle<InputTarget>();
        target->key = aAxis;
        target->threshold = aThreshold;

        return target;
    }

    Red::EInputAction action{Red::EInputAction::IACT_None};
    Red::EInputKey key{Red::EInputKey::IK_None};
    float threshold{};

    RTTI_IMPL_TYPEINFO(App::InputTarget);
    RTTI_IMPL_ALLOCATOR();
};
}

RTTI_DEFINE_CLASS(App::InputTarget, {
    RTTI_PARENT(App::CallbackSystemTarget);
    RTTI_METHOD(Key);
    RTTI_METHOD(Axis);
});
