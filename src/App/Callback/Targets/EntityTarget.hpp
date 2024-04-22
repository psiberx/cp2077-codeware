#pragma once

#include "App/Callback/CallbackSystemTarget.hpp"
#include "App/Callback/Events/EntityLifecycleEvent.hpp"
#include "Red/Entity.hpp"

namespace App
{
struct EntityTarget : CallbackSystemTarget
{
    EntityTarget() = default;

    bool Matches(const Red::Handle<CallbackSystemEvent>& aEvent) override
    {
        auto* entity = aEvent.GetPtr<EntityLifecycleEvent>()->entity.instance;

        if (entityID && entityID != Raw::Entity::EntityID::Ref(entity))
            return false;

        if (entityType && !entity->GetType()->IsA(entityType))
            return false;

        if (templatePath && templatePath != Raw::Entity::TemplatePath::Ref(entity))
            return false;

        if (appearanceName && appearanceName != Raw::Entity::AppearanceName::Ref(entity))
            return false;

        return true;
    }

    bool Equals(const Red::Handle<CallbackSystemTarget>& aTarget) override
    {
        const auto* target = aTarget.GetPtr<EntityTarget>();

        return entityID == target->entityID && entityType == target->entityType &&
               templatePath == target->templatePath && appearanceName == target->appearanceName;
    }

    static Red::Handle<EntityTarget> ID(Red::EntityID aEntityID)
    {
        auto target = Red::MakeHandle<EntityTarget>();
        target->entityID = aEntityID;

        return target;
    }

    static Red::Handle<EntityTarget> Type(Red::CName aEntityType)
    {
        auto target = Red::MakeHandle<EntityTarget>();
        target->entityType = Red::GetClass(aEntityType);

        return target;
    }

    static Red::Handle<EntityTarget> Template(const Red::RaRef<>& aTemplate)
    {
        auto target = Red::MakeHandle<EntityTarget>();
        target->templatePath = aTemplate.path;

        return target;
    }

    static Red::Handle<EntityTarget> Appearance(Red::CName aAppearance)
    {
        auto target = Red::MakeHandle<EntityTarget>();
        target->appearanceName = aAppearance;

        return target;
    }

    Red::EntityID entityID{};
    Red::CClass* entityType{};
    Red::ResourcePath templatePath{};
    Red::CName appearanceName{};

    RTTI_IMPL_TYPEINFO(App::EntityTarget);
    RTTI_IMPL_ALLOCATOR();
};
}

RTTI_DEFINE_CLASS(App::EntityTarget, {
    RTTI_PARENT(App::CallbackSystemTarget);
    RTTI_METHOD(ID);
    RTTI_METHOD(Type);
    RTTI_METHOD(Template);
    RTTI_METHOD(Appearance);
});
