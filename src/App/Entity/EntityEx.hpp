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

    Red::DynArray<Red::Handle<Red::IComponent>> GetComponents()
    {
        return Raw::Entity::ComponentsStorage(this)->components;
    }

    void AddComponent(const Red::Handle<Red::IComponent>& aComponent)
    {
        Raw::Entity::ComponentsStorage(this)->components.PushBack(aComponent);
    }
};
}

RTTI_EXPAND_CLASS(Red::Entity, App::EntityEx, {
    RTTI_METHOD(GetTemplatePath);
    RTTI_METHOD(GetComponents);
    RTTI_METHOD(AddComponent);
});
