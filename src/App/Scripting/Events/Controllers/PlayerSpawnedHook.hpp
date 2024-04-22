#pragma once

#include "App/Scripting/Events/GameSessionEvent.hpp"
#include "App/Scripting/CallbackSystem.hpp"
#include "App/Scripting/EventController.hpp"
#include "Core/Hooking/HookingAgent.hpp"
#include "Red/PlayerSystem.hpp"

namespace App
{
class PlayerSpawnedHook
    : public EventController
    , public Core::HookingAgent
{
public:
    constexpr static auto EventName = Red::CName("Session/Ready");

    Core::Vector<Red::CName> GetEvents() override
    {
        return {EventName};
    }

protected:
    bool OnActivateHook() override
    {
        return IsHooked<Raw::PlayerSystem::OnPlayerSpawned>() || HookAfter<Raw::PlayerSystem::OnPlayerSpawned>(&OnPlayerSpawned);
    }

    bool OnDeactivateHook() override
    {
        return !IsHooked<Raw::PlayerSystem::OnPlayerSpawned>() || Unhook<Raw::PlayerSystem::OnPlayerSpawned>();
    }

    inline static void OnPlayerSpawned()
    {
        auto system = CallbackSystem::Get();
        if (!system->IsRestored())
        {
            system->TriggerEvent<GameSessionEvent>(EventName, system->IsPreGame(), system->IsRestored());
        }
    }
};
}
