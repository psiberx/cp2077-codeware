#pragma once

#include "App/Callback/CallbackSystemTarget.hpp"
#include "App/Callback/Events/ResourceEvent.hpp"

namespace App
{
struct ResourceTarget : CallbackSystemTarget
{
    ResourceTarget() = default;

    ResourceTarget(Red::ResourcePath aPath)
        : path(aPath)
    {
    }

    ResourceTarget(Red::CClass* aType)
        : type(aType)
    {
    }

    bool Matches(const Red::Handle<CallbackSystemEvent>& aEvent) override
    {
        const auto* event = aEvent.GetPtr<ResourceEvent>();

        if (path && event->resource->path != path)
            return false;

        if (type && !event->resource->GetNativeType()->IsA(type))
            return false;

        return true;
    }

    bool Equals(const Red::Handle<CallbackSystemTarget>& aTarget) override
    {
        const auto* target = aTarget.GetPtr<ResourceTarget>();

        return path == target->path && type == target->type;
    }

    bool Supports(Red::CName aEventType) override
    {
        return aEventType == Red::GetTypeName<ResourceEvent>();
    }

    static Red::Handle<ResourceTarget> Path(const Red::RaRef<>& aRef)
    {
        return Red::MakeHandle<ResourceTarget>(aRef.path);
    }

    static Red::Handle<ResourceTarget> Type(Red::CName aType)
    {
        return Red::MakeHandle<ResourceTarget>(Red::GetClass(aType));
    }

    Red::ResourcePath path{};
    Red::CClass* type{};

    RTTI_IMPL_TYPEINFO(App::ResourceTarget);
    RTTI_IMPL_ALLOCATOR();
};
}

RTTI_DEFINE_CLASS(App::ResourceTarget, {
    RTTI_PARENT(App::CallbackSystemTarget);
    RTTI_METHOD(Path);
    RTTI_METHOD(Type);
});
