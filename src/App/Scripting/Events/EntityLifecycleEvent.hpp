#pragma once

#include "App/Scripting/EventObject.hpp"

namespace App
{
struct EntityLifecycleEvent : NamedEvent
{
    EntityLifecycleEvent() = default;

    EntityLifecycleEvent(Red::CName aName, Red::WeakHandle<Red::Entity> aEntity)
        : NamedEvent(aName)
        , entity(std::move(aEntity))
    {
    }

    Red::WeakHandle<Red::Entity> entity;

    RTTI_IMPL_TYPEINFO(App::EntityLifecycleEvent);
    RTTI_IMPL_ALLOCATOR();
};
}

RTTI_DEFINE_CLASS(App::EntityLifecycleEvent, {
    RTTI_PARENT(App::NamedEvent);
    RTTI_GETTER(entity);
});
