#pragma once

#include "App/Callback/CallbackSystemTarget.hpp"
#include "App/Callback/Events/InkWidgetSpawnEvent.hpp"

namespace App
{
struct inkWidgetTarget : CallbackSystemTarget
{
    inkWidgetTarget() = default;

    bool Matches(const Red::Handle<CallbackSystemEvent>& aEvent) override
    {
        const auto* event = aEvent.GetPtr<inkWidgetSpawnEvent>();

        if (libraryPath && libraryPath != event->libraryPath)
            return false;

        if (itemName && itemName != event->itemName)
            return false;

        if (controllerType && (!event->itemInstance->gameController ||
                               !Red::IsInstanceOf(event->itemInstance->gameController, controllerType)))
            return false;

        return true;
    }

    bool Equals(const Red::Handle<CallbackSystemTarget>& aTarget) override
    {
        const auto* target = aTarget.GetPtr<inkWidgetTarget>();

        return libraryPath == target->libraryPath && itemName == target->itemName &&
               controllerType == target->controllerType;
    }

    bool Supports(Red::CName aEventType) override
    {
        return aEventType == Red::GetTypeName<inkWidgetSpawnEvent>();
    }

    static Red::Handle<inkWidgetTarget> Library(Red::ResourcePath aPath, Red::Optional<Red::CName> aItem)
    {
        auto target = Red::MakeHandle<inkWidgetTarget>();
        target->libraryPath = aPath;
        target->itemName = aItem;

        return target;
    }

    static Red::Handle<inkWidgetTarget> Controller(Red::CName aController)
    {
        auto target = Red::MakeHandle<inkWidgetTarget>();
        target->controllerType = aController;

        return target;
    }

    Red::ResourcePath libraryPath{};
    Red::CName itemName{};
    Red::CName controllerType{};

    RTTI_IMPL_TYPEINFO(App::inkWidgetTarget);
    RTTI_IMPL_ALLOCATOR();
};
}

RTTI_DEFINE_CLASS(App::inkWidgetTarget, {
    RTTI_PARENT(App::CallbackSystemTarget);
    RTTI_METHOD(Library);
    RTTI_METHOD(Controller);
});
