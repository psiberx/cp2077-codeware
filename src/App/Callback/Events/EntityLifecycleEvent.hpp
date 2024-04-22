#pragma once

#include "App/Callback/CallbackSystemEvent.hpp"

namespace App
{
struct EntityLifecycleEvent : CallbackSystemEvent
{
    EntityLifecycleEvent() = default;

    EntityLifecycleEvent(Red::CName aName, Red::WeakHandle<Red::Entity> aEntity)
        : CallbackSystemEvent(aName)
        , entity(std::move(aEntity))
    {
    }

    Red::WeakHandle<Red::Entity> entity;

    RTTI_IMPL_TYPEINFO(App::EntityLifecycleEvent);
    RTTI_IMPL_ALLOCATOR();
};
}

RTTI_DEFINE_CLASS(App::EntityLifecycleEvent, {
    RTTI_PARENT(App::CallbackSystemEvent);
    RTTI_GETTER(entity);
});
