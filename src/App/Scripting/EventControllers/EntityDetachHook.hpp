#pragma once

#include "EntityLifecycleEvent.hpp"
#include "App/Scripting/CallbackSystem.hpp"
#include "App/Scripting/EventController.hpp"
#include "Core/Hooking/HookingAgent.hpp"
#include "Red/Entity.hpp"

namespace App
{
class EntityDetachHook
    : public EventController
    , public Core::HookingAgent
{
public:
    constexpr static auto EventName = Red::CName("Entity/Detach");

    Core::Vector<Red::CName> GetEvents() override
    {
        return {EventName};
    }

    bool Initialize() override
    {
        return IsHooked<Raw::Entity::Detach>() || HookBefore<Raw::Entity::Detach>(&OnDetach);
    }

    bool Uninitialize() override
    {
        return !IsHooked<Raw::Entity::Detach>() || Unhook<Raw::Entity::Detach>();
    }

protected:
    inline static void OnDetach(Red::Entity* aEntity)
    {
        CallbackSystem::PassEvent<EntityLifecycleEvent>(EventName, Red::AsWeakHandle(aEntity));
    }
};
}
