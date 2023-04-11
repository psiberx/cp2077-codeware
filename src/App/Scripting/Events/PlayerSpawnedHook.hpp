#pragma once

#include "GameSessionEvent.hpp"
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

    bool Initialize() override
    {
        return IsHooked<Raw::PlayerSystem::OnPlayerSpawned>() || HookAfter<Raw::PlayerSystem::OnPlayerSpawned>(&OnPlayerSpawned);
    }

    bool Uninitialize() override
    {
        return !IsHooked<Raw::PlayerSystem::OnPlayerSpawned>() || Unhook<Raw::PlayerSystem::OnPlayerSpawned>();
    }

protected:
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
