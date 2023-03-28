#pragma once

#include "Red/Entity.hpp"

namespace App
{
struct EntityEx : Red::ent::Entity
{
    Red::DynArray<Red::Handle<Red::ent::IComponent>> GetComponents()
    {
        return Raw::Entity::GetComponents(this);
    }
};
}

RTTI_EXPAND_CLASS(Red::ent::Entity, App::EntityEx, {
    RTTI_METHOD(GetComponents);
});
