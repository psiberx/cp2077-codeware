#pragma once

#include "App/Callback/CallbackSystemEvent.hpp"

namespace App
{
struct ResourceEvent : CallbackSystemEvent
{
    ResourceEvent() = default;

    ResourceEvent(Red::CName aName, Red::Handle<Red::CResource> aResource)
        : CallbackSystemEvent(aName)
        , resource(std::move(aResource))
    {
    }

    Red::RaRef<> GetPath()
    {
        return resource->path;
    }

    Red::Handle<Red::CResource> resource;

    RTTI_IMPL_TYPEINFO(App::ResourceEvent);
    RTTI_IMPL_ALLOCATOR();
};
}

RTTI_DEFINE_CLASS(App::ResourceEvent, {
    RTTI_PARENT(App::CallbackSystemEvent);
    RTTI_METHOD(GetPath);
    RTTI_GETTER(resource);
});
