#pragma once

#include "Red/Entity.hpp"

namespace App
{
struct EntityEx : Red::Entity
{
    Red::ResourceAsyncReference<> GetTemplatePath()
    {
        return templatePath;
    }

    Red::Handle<Red::IComponent> FindComponentByType(Red::CName aType)
    {
        if (auto type = Red::GetClass(aType))
        {
            for (const auto& component : components)
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
        return components;
    }

    void AddComponent(const Red::Handle<Red::IComponent>& aComponent)
    {
        aComponent->owner = this;

        components.PushBack(aComponent);
    }

    void SetWorldTransform(const Red::WorldTransform& aTransform)
    {
        Raw::IPlacedComponent::SetTransform(transformComponent, aTransform);
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
