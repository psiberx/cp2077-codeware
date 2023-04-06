#pragma once

#include "Red/Entity.hpp"

namespace App
{
struct EntityEx : Red::Entity
{
    static constexpr auto TemplatePathOffset = 0x60;
    static constexpr auto ComponentsOffset = 0x70;

    Red::ResourceAsyncReference<> GetTemplatePath()
    {
        return *Core::OffsetPtr<Red::ResourceAsyncReference<>>(this, TemplatePathOffset);
    }

    Red::DynArray<Red::Handle<Red::IComponent>> GetComponents()
    {
        auto storage = Core::OffsetPtr<Red::ent::ComponentsStorage>(this, ComponentsOffset);
        return storage->components;
        // return Raw::Entity::GetComponents(this);
    }

    void AddComponent(const Red::Handle<Red::IComponent>& aComponent)
    {
        auto storage = Core::OffsetPtr<Red::ent::ComponentsStorage>(this, ComponentsOffset);
        storage->components.PushBack(aComponent);
    }
};
}

RTTI_EXPAND_CLASS(Red::Entity, {
    RTTI_METHOD_FQN(App::EntityEx::GetTemplatePath);
    RTTI_METHOD_FQN(App::EntityEx::GetComponents);
    RTTI_METHOD_FQN(App::EntityEx::AddComponent);
});
