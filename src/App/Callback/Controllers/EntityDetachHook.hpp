#pragma once

#include "App/Callback/CallbackSystem.hpp"
#include "App/Callback/CallbackSystemController.hpp"
#include "App/Callback/Events/EntityLifecycleEvent.hpp"
#include "Core/Hooking/HookingAgent.hpp"
#include "Red/Entity.hpp"

namespace App
{
class EntityDetachHook
    : public CallbackSystemController
    , public Core::HookingAgent
{
public:
    constexpr static auto EventName = Red::CName("Entity/Detach");

    Core::Vector<Red::CName> GetEvents() override
    {
        return {EventName};
    }

protected:
    bool OnActivateHook() override
    {
        return IsHooked<Raw::Entity::Detach>() || HookBefore<Raw::Entity::Detach>(&OnDetach);
    }

    bool OnDeactivateHook() override
    {
        return !IsHooked<Raw::Entity::Detach>() || Unhook<Raw::Entity::Detach>();
    }

    inline static void OnDetach(Red::Entity* aEntity)
    {
        CallbackSystem::PassEvent<EntityLifecycleEvent>(EventName, Red::AsWeakHandle(aEntity));
    }
};
}
