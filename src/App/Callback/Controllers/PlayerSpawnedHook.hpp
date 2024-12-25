#pragma once

#include "App/Callback/CallbackSystem.hpp"
#include "App/Callback/CallbackSystemController.hpp"
#include "App/Callback/Events/GameSessionEvent.hpp"
#include "Core/Hooking/HookingAgent.hpp"
#include "Red/PlayerSystem.hpp"

namespace App
{
class PlayerSpawnedHook
    : public CallbackSystemController
    , public Core::HookingAgent
{
public:
    Core::Map<Red::CName, Red::CName> GetEvents() override
    {
        return {{CallbackSystem::SessionReadyEventName, Red::GetTypeName<EntityLifecycleEvent>()}};
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
        auto callbackSystem = CallbackSystem::Get();
        if (!callbackSystem->IsRestored())
        {
            callbackSystem->DispatchNativeEvent<GameSessionEvent>(CallbackSystem::SessionReadyEventName,
                                                                  callbackSystem->IsPreGame(),
                                                                  callbackSystem->IsRestored());
        }
    }
};
}
