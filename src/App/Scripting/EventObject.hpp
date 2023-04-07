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

    Red::CName eventName;

    RTTI_IMPL_TYPEINFO(App::NamedEvent);
    RTTI_IMPL_ALLOCATOR();
};
}

RTTI_DEFINE_CLASS(App::NamedEvent, {
    RTTI_ABSTRACT();
    RTTI_GETTER(eventName);
});
