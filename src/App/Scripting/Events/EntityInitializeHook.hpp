#pragma once

#include "EntityLifecycleEvent.hpp"
#include "App/Scripting/CallbackSystem.hpp"
#include "App/Scripting/EventController.hpp"
#include "Core/Hooking/HookingAgent.hpp"
#include "Red/Entity.hpp"

namespace App
{
class EntityInitializeHook
    : public EventController
    , public Core::HookingAgent
{
public:
    constexpr static auto EventName = Red::CName("Entity/Initialize");

    Core::Vector<Red::CName> GetEvents() override
    {
        return {EventName};
    }

protected:
    bool OnActivateHook() override
    {
        return IsHooked<Raw::Entity::Initialize>() || HookBefore<Raw::Entity::Initialize>(&OnInitialize);
    }

    bool OnDeactivateHook() override
    {
        return !IsHooked<Raw::Entity::Initialize>() || Unhook<Raw::Entity::Initialize>();
    }

    inline static void OnInitialize(Red::Entity* aEntity, uintptr_t a2, Red::EntityInitializeRequest* aRequest)
    {
        if (aRequest->entityID)
        {
            Raw::Entity::EntityID{aEntity} = aRequest->entityID;
        }

        CallbackSystem::PassEvent<EntityLifecycleEvent>(EventName, Red::AsWeakHandle(aEntity));
    }
};
}
