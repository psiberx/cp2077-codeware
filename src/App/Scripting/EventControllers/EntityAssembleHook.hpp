#pragma once

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
    constexpr static auto AssembleEvent = Red::CName("Entity/Assemble");

    Core::Vector<Red::CName> GetEvents() override
    {
        return {AssembleEvent};
    }

    bool Initialize() override
    {
        return IsHooked<Raw::Entity::OnAssemble>()
            || HookAfter<Raw::Entity::OnAssemble>(&OnAssemble);
    }

    bool Uninitialize() override
    {
        return !IsHooked<Raw::Entity::OnAssemble>()
            || Unhook<Raw::Entity::OnAssemble>();
    }

protected:
    inline static void OnAssemble(Red::Entity* aEntity, uintptr_t a2, uintptr_t a3)
    {
        CallbackSystem::PassEvent(AssembleEvent, Red::AsWeakHandle(aEntity));
    }
};
}
