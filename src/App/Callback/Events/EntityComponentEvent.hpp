#pragma once

#include "App/Callback/Events/EntityLifecycleEvent.hpp"

namespace App
{
struct EntityComponentEvent : EntityLifecycleEvent
{
    EntityComponentEvent() = default;

    EntityComponentEvent(Red::CName aName, Red::WeakHandle<Red::Entity> aEntity,
                         Red::WeakHandle<Red::IComponent> aComponent)
        : EntityLifecycleEvent(aName, std::move(aEntity))
        , component(std::move(aComponent))
    {
    }

    Red::WeakHandle<Red::IComponent> component;

    RTTI_IMPL_TYPEINFO(App::EntityComponentEvent);
    RTTI_IMPL_ALLOCATOR();
};
}

RTTI_DEFINE_CLASS(App::EntityComponentEvent, {
    RTTI_PARENT(App::EntityLifecycleEvent);
    RTTI_GETTER(component);
});
