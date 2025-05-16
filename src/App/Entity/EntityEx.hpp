#pragma once

#include "Red/Entity.hpp"

namespace App
{
struct EntityEx : Red::Entity
{
    Red::ResourceAsyncReference<> GetTemplatePath()
    {
        return *Raw::Entity::TemplatePath(this);
    }

    Red::Handle<Red::IComponent> FindComponentByType(Red::CName aType)
    {
        if (auto type = Red::GetClass(aType))
        {
            for (const auto& component : Raw::Entity::ComponentsStorage::Ptr(this)->components)
            {
                if (component->GetType()->IsA(type))
                {
                    return component;
                }
            }
        }
        return {};
    }

    Red::DynArray<Red::Handle<Red::IComponent>> GetComponents()
    {
        return Raw::Entity::ComponentsStorage(this)->components;
    }

    void AddComponent(const Red::Handle<Red::IComponent>& aComponent)
    {
        Raw::Entity::ComponentsStorage(this)->components.PushBack(aComponent);
    }

    void SetWorldTransform(const Red::WorldTransform& aTransform)
    {
        Raw::IPlacedComponent::SetTransform(Raw::Entity::TransformComponent::Ref(this), aTransform);
    }

    bool ApplyMorphTarget(Red::CName aTarget, Red::CName aRegion, float aValue);
};
}

RTTI_EXPAND_CLASS(Red::Entity, App::EntityEx, {
    RTTI_METHOD(GetTemplatePath);
    RTTI_METHOD(FindComponentByType);
    RTTI_METHOD(GetComponents);
    RTTI_METHOD(AddComponent);
    RTTI_METHOD(SetWorldTransform);
    RTTI_METHOD(ApplyMorphTarget);
});
