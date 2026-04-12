#pragma once

#include "App/Callback/CallbackSystemEvent.hpp"
#include "App/Engine/JobQueue.hpp"

namespace App
{
struct ResourceEvent : CallbackSystemEvent
{
    ResourceEvent() = default;

    ResourceEvent(Red::CName aName, Red::Handle<Red::CResource> aResource)
        : CallbackSystemEvent(aName)
        , resource(std::move(aResource))
        , jobGroup()
    {
    }

    ResourceEvent(Red::CName aName, Red::Handle<Red::CResource> aResource, const Red::JobGroup& aJobGroup)
        : CallbackSystemEvent(aName)
        , resource(std::move(aResource))
        , jobGroup(aJobGroup)
    {
    }

    [[nodiscard]] Red::RaRef<> GetPath() const
    {
        return resource->path;
    }

    [[nodiscard]] App::JobGroup GetJobGroup() const
    {
        return jobGroup;
    }

    Red::Handle<Red::CResource> resource;
    App::JobGroup jobGroup;

    RTTI_IMPL_TYPEINFO(App::ResourceEvent);
    RTTI_IMPL_ALLOCATOR();
};
}

RTTI_DEFINE_CLASS(App::ResourceEvent, {
    RTTI_PARENT(App::CallbackSystemEvent);
    RTTI_METHOD(GetPath);
    RTTI_METHOD(GetJobGroup);
    RTTI_GETTER(resource);
});
