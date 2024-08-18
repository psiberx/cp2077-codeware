#pragma once

#include "App/Callback/CallbackSystemEvent.hpp"
#include "App/Callback/Events/EntityLifecycleEvent.hpp"

namespace App
{
struct VehicleLightControlEvent : EntityLifecycleEvent
{
    VehicleLightControlEvent() = default;

    VehicleLightControlEvent(Red::CName aName, Red::WeakHandle<Red::Entity> aEntity,
                             bool aEnable, Red::vehicleELightType aLightType)
        : EntityLifecycleEvent(aName, std::move(aEntity))
        , enabled(aEnable)
        , lightType(aLightType)
    {
    }

    [[nodiscard]] bool IsLightType(Red::vehicleELightType aLightType) const
    {
        return (static_cast<uint32_t>(lightType) & static_cast<uint32_t>(aLightType)) != 0;
    }

    bool enabled;
    Red::vehicleELightType lightType;

    RTTI_IMPL_TYPEINFO(App::VehicleLightControlEvent);
    RTTI_IMPL_ALLOCATOR();
};
}

RTTI_DEFINE_CLASS(App::VehicleLightControlEvent, {
    RTTI_PARENT(App::EntityLifecycleEvent);
    RTTI_METHOD(IsLightType);
    RTTI_GETTER(enabled);
});
