#pragma once

#include "App/Callback/CallbackSystemEvent.hpp"

namespace App
{
struct inkWidgetSpawnEvent : CallbackSystemEvent
{
    inkWidgetSpawnEvent() = default;

    inkWidgetSpawnEvent(Red::CName aEventName, Red::ResourcePath aLibraryPath, Red::CName aItemName,
                        const Red::Handle<Red::ink::WidgetLibraryItemInstance>& aItemInstance)
        : CallbackSystemEvent(aEventName)
        , libraryPath(aLibraryPath)
        , itemName(aItemName)
        , itemInstance(aItemInstance)
    {
    }

    Red::Handle<Red::ink::WidgetLibraryItemInstance> itemInstance;
    Red::ResourcePath libraryPath;
    Red::CName itemName;

    RTTI_IMPL_TYPEINFO(App::inkWidgetSpawnEvent);
    RTTI_IMPL_ALLOCATOR();
};
}

RTTI_DEFINE_CLASS(App::inkWidgetSpawnEvent, {
    RTTI_PARENT(App::CallbackSystemEvent);
    RTTI_GETTER(libraryPath);
    RTTI_GETTER(itemName);
    RTTI_GETTER(itemInstance);
});
