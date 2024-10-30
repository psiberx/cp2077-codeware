#pragma once

#include "App/Callback/CallbackSystem.hpp"
#include "App/Callback/CallbackSystemController.hpp"
#include "App/Callback/Events/EntityLifecycleEvent.hpp"
#include "Core/Hooking/HookingAgent.hpp"
#include "Red/Entity.hpp"

namespace App
{
class EntityInitializeHook
    : public CallbackSystemController
    , public Core::HookingAgent
{
public:
    constexpr static auto EventName = Red::CName("Entity/Initialize");

    Core::Map<Red::CName, Red::CName> GetEvents() override
    {
        return {{EventName, Red::GetTypeName<EntityLifecycleEvent>()}};
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
            Raw::Entity::EntityID::Set(aEntity, aRequest->entityID);
        }

        CallbackSystem::Get()->DispatchNativeEvent<EntityLifecycleEvent>(EventName, Red::AsWeakHandle(aEntity));
    }
};
}
