#pragma once

namespace App
{
struct NamedEvent : Red::IScriptable
{
    NamedEvent() = default;

    explicit NamedEvent(Red::CName aName)
        : eventName(aName)
    {
    }

    void InitEvent(Red::CName aEventName)
    {
        if (!eventName)
        {
            eventName = aEventName;
        }
    }

    Red::CName eventName;

    RTTI_IMPL_TYPEINFO(App::NamedEvent);
    RTTI_IMPL_ALLOCATOR();
};
}

RTTI_DEFINE_CLASS(App::NamedEvent, {
    RTTI_ABSTRACT();
    RTTI_METHOD(InitEvent);
    RTTI_GETTER(eventName);
});
