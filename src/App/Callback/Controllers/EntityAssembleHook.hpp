#pragma once

#include "App/Callback/CallbackSystem.hpp"
#include "App/Callback/CallbackSystemController.hpp"
#include "App/Callback/Events/EntityLifecycleEvent.hpp"
#include "Core/Hooking/HookingAgent.hpp"
#include "Red/Entity.hpp"

namespace App
{
class EntityAssembleHook
    : public CallbackSystemController
    , public Core::HookingAgent
{
public:
    constexpr static auto EventName = Red::CName("Entity/Assemble");

    Core::Map<Red::CName, Red::CName> GetEvents() override
    {
        return {{EventName, Red::GetTypeName<EntityLifecycleEvent>()}};
    }

protected:
    bool OnActivateHook() override
    {
        return IsHooked<Raw::Entity::OnAssemble>() || HookAfter<Raw::Entity::OnAssemble>(&OnAssemble);
    }

    bool OnDeactivateHook() override
    {
        return !IsHooked<Raw::Entity::OnAssemble>() || Unhook<Raw::Entity::OnAssemble>();
    }

    inline static void OnAssemble(Red::Entity* aEntity, uintptr_t)
    {
        CallbackSystem::PassEvent<EntityLifecycleEvent>(EventName, Red::AsWeakHandle(aEntity));
    }
};
}
