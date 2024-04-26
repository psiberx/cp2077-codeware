#pragma once

#include "App/Callback/CallbackSystemTarget.hpp"
#include "App/Callback/Events/EntityLifecycleEvent.hpp"
#include "App/World/StaticEntitySystem.hpp"
#include "Red/Entity.hpp"

namespace App
{
struct StaticEntityTarget : CallbackSystemTarget
{
    StaticEntityTarget() = default;

    bool Matches(const Red::Handle<CallbackSystemEvent>& aEvent) override
    {
        auto* entity = aEvent.GetPtr<EntityLifecycleEvent>()->entity.instance;

        if (tags.empty())
            return true;

        auto& entityID = Raw::Entity::EntityID::Ref(entity);
        auto entitySystem = Red::GetGameSystem<StaticEntitySystem>();

        if (!entityID || !entitySystem)
            return false;

        for (const auto& tag : tags)
        {
            if (entitySystem->IsTagged(entityID, tag))
                return true;
        }

        return false;
    }

    bool Equals(const Red::Handle<CallbackSystemTarget>& aTarget) override
    {
        const auto* target = aTarget.GetPtr<StaticEntityTarget>();

        return tags == target->tags;
    }

    bool Supports(Red::CName aEventType) override
    {
        return aEventType == Red::GetTypeName<EntityLifecycleEvent>();
    }

    static Red::Handle<StaticEntityTarget> Tag(Red::CName aTag)
    {
        auto target = Red::MakeHandle<StaticEntityTarget>();
        target->tags.insert(aTag);

        return target;
    }

    static Red::Handle<StaticEntityTarget> Tags(const Red::DynArray<Red::CName>& aTags)
    {
        auto target = Red::MakeHandle<StaticEntityTarget>();
        for (const auto& tag : aTags)
        {
            target->tags.insert(tag);
        }

        return target;
    }

    Core::Set<Red::CName> tags{};

    RTTI_IMPL_TYPEINFO(App::StaticEntityTarget);
    RTTI_IMPL_ALLOCATOR();
};
}

RTTI_DEFINE_CLASS(App::StaticEntityTarget, {
    RTTI_PARENT(App::CallbackSystemTarget);
    RTTI_METHOD(Tag);
    RTTI_METHOD(Tags);
});
