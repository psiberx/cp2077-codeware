#pragma once

#include "Red/Entity.hpp"

namespace App
{
struct EntityEx : Red::Entity
{
    Red::DynArray<Red::Handle<Red::ent::IComponent>> GetComponents()
    {
        return Raw::Entity::GetComponents(this);
    }
};
}

RTTI_EXPAND_CLASS(Red::Entity, {
    RTTI_METHOD_FQN(App::EntityEx::GetComponents);
});
