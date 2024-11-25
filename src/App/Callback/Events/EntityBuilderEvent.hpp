#pragma once

#include "App/Callback/CallbackSystemEvent.hpp"
#include "App/Entity/EntityBuilderWrapper.hpp"

namespace App
{
struct EntityBuilderEvent : CallbackSystemEvent
{
    EntityBuilderEvent() = default;

    EntityBuilderEvent(Red::CName aName, const Red::WeakPtr<Red::EntityBuilder>& aEntityBuilder)
        : CallbackSystemEvent(aName)
        , entityBuilder(Red::MakeHandle<EntityBuilderWrapper>(aEntityBuilder))
    {
    }

    Red::Handle<EntityBuilderWrapper> entityBuilder;

    RTTI_IMPL_TYPEINFO(App::EntityBuilderEvent);
    RTTI_IMPL_ALLOCATOR();
};
}

RTTI_DEFINE_CLASS(App::EntityBuilderEvent, {
    RTTI_PARENT(App::CallbackSystemEvent);
    RTTI_GETTER(entityBuilder);
});
