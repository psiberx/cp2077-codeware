#pragma once

#include "App/Callback/CallbackSystemTarget.hpp"
#include "App/Callback/Events/EntityComponentEvent.hpp"

namespace App
{
struct ComponentTarget : CallbackSystemTarget
{
    ComponentTarget() = default;

    bool Matches(const Red::Handle<CallbackSystemEvent>& aEvent) override
    {
        auto* component = aEvent.GetPtr<EntityComponentEvent>()->component.instance;

        if (componentName && componentName != component->name)
            return false;

        if (componentID.unk00 && componentID.unk00 != component->id.unk00)
            return false;

        return true;
    }

    bool Equals(const Red::Handle<CallbackSystemTarget>& aTarget) override
    {
        const auto* target = aTarget.GetPtr<ComponentTarget>();

        return componentID.unk00 == target->componentID.unk00 && componentName == target->componentName;
    }

    bool Supports(Red::CName aEventType) override
    {
        return aEventType == Red::GetTypeName<EntityComponentEvent>();
    }

    static Red::Handle<ComponentTarget> ID(Red::CRUID aID)
    {
        auto target = Red::MakeHandle<ComponentTarget>();
        target->componentID = aID;

        return target;
    }

    static Red::Handle<ComponentTarget> Name(Red::CName aName)
    {
        auto target = Red::MakeHandle<ComponentTarget>();
        target->componentName = aName;

        return target;
    }
    
    Red::CRUID componentID{};
    Red::CName componentName{};

    RTTI_IMPL_TYPEINFO(App::ComponentTarget);
    RTTI_IMPL_ALLOCATOR();
};
}

RTTI_DEFINE_CLASS(App::ComponentTarget, {
    RTTI_PARENT(App::CallbackSystemTarget);
    RTTI_METHOD(ID);
    RTTI_METHOD(Name);
});
