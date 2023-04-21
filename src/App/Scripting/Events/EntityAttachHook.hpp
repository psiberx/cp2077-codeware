#pragma once

#include "EntityLifecycleEvent.hpp"
#include "App/Scripting/CallbackSystem.hpp"
#include "App/Scripting/EventController.hpp"
#include "Core/Hooking/HookingAgent.hpp"
#include "Red/Entity.hpp"

namespace App
{
class EntityAttachHook
    : public EventController
    , public Core::HookingAgent
{
public:
    constexpr static auto EventName = Red::CName("Entity/Attach");
    constexpr static auto PostEventName = Red::CName("Entity/Attached");

    Core::Vector<Red::CName> GetEvents() override
    {
        return {EventName, PostEventName};
    }

    bool Initialize() override
    {
        return IsHooked<Raw::Entity::Attach>() || Hook<Raw::Entity::Attach>(&OnAttach);
    }

    bool Uninitialize() override
    {
        return !IsHooked<Raw::Entity::Attach>() || Unhook<Raw::Entity::Attach>();
    }

protected:
    inline static void OnAttach(Red::Entity* aEntity, uintptr_t a2)
    {
        CallbackSystem::PassEvent<EntityLifecycleEvent>(EventName, Red::AsWeakHandle(aEntity));
        Raw::Entity::Attach(aEntity, a2);
        CallbackSystem::PassEvent<EntityLifecycleEvent>(PostEventName, Red::AsWeakHandle(aEntity));
    }
};
}
