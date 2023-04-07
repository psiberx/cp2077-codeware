#pragma once

#include "EntityLifecycleEvent.hpp"
#include "App/Scripting/CallbackSystem.hpp"
#include "App/Scripting/EventController.hpp"
#include "Core/Hooking/HookingAgent.hpp"
#include "Red/Entity.hpp"

namespace App
{
class EntityUninitializeHook
    : public EventController
    , public Core::HookingAgent
{
public:
    constexpr static auto EventName = Red::CName("Entity/Uninitialize");

    Core::Vector<Red::CName> GetEvents() override
    {
        return {EventName};
    }

    bool Initialize() override
    {
        return (IsHooked<Raw::Entity::Uninitialize>() || HookBefore<Raw::Entity::Uninitialize>(&OnUninitialize))
            && (IsHooked<Raw::Entity::Dispose>() || HookBefore<Raw::Entity::Dispose>(&OnDispose));
    }

    bool Uninitialize() override
    {
        return (!IsHooked<Raw::Entity::Uninitialize>() || Unhook<Raw::Entity::Uninitialize>())
            && (!IsHooked<Raw::Entity::Dispose>() || Unhook<Raw::Entity::Dispose>());
    }

protected:
    inline static void OnUninitialize(Red::Entity* aEntity)
    {
        CallbackSystem::PassEvent<EntityLifecycleEvent>(EventName, Red::AsWeakHandle(aEntity));
    }

    inline static void OnDispose(Red::Entity* aEntity)
    {
        const auto scene = Raw::Entity::Scene(aEntity);
        const auto status = Raw::Entity::Status(aEntity);

        if (status < Red::EntityStatus::Uninitializing && !scene)
        {
            CallbackSystem::PassEvent<EntityLifecycleEvent>(EventName, Red::AsWeakHandle(aEntity));
        }
    }
};
}
