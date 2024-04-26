#pragma once

namespace App
{
struct CallbackSystemEvent : Red::IScriptable
{
    CallbackSystemEvent() = default;

    explicit CallbackSystemEvent(Red::CName aName)
        : eventName(aName)
    {
    }

    void SetEventName(Red::CName aEventName)
    {
        if (!eventName)
        {
            eventName = aEventName;
        }
    }

    Red::CName eventName;

    RTTI_IMPL_TYPEINFO(App::CallbackSystemEvent);
    RTTI_IMPL_ALLOCATOR();
};
}

RTTI_DEFINE_CLASS(App::CallbackSystemEvent, {
    RTTI_ABSTRACT();
    RTTI_GETTER(eventName);
});
