#pragma once

#include "EntityLifecycleEvent.hpp"
#include "App/Scripting/CallbackSystem.hpp"
#include "App/Scripting/EventController.hpp"
#include "Core/Hooking/HookingAgent.hpp"
#include "Red/Entity.hpp"

namespace App
{
class EntityAssembleHook
    : public EventController
    , public Core::HookingAgent
{
public:
    constexpr static auto EventName = Red::CName("Entity/Assemble");

    Core::Vector<Red::CName> GetEvents() override
    {
        return {EventName};
    }

    bool Initialize() override
    {
        return IsHooked<Raw::Entity::OnAssemble>() || HookAfter<Raw::Entity::OnAssemble>(&OnAssemble);
    }

    bool Uninitialize() override
    {
        return !IsHooked<Raw::Entity::OnAssemble>() || Unhook<Raw::Entity::OnAssemble>();
    }

protected:
    inline static void OnAssemble(Red::Entity* aEntity, uintptr_t, uintptr_t)
    {
        CallbackSystem::PassEvent<EntityLifecycleEvent>(EventName, Red::AsWeakHandle(aEntity));
    }
};
}
