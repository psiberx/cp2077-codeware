#pragma once

#include "App/Callback/CallbackSystem.hpp"
#include "App/Callback/CallbackSystemController.hpp"
#include "App/Callback/MacHooks.hpp"
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
#if defined(__APPLE__)
    // R18. The hooks are installed once at plugin load (InstallMacCallbackHooks); activation has nothing to do.
public:
    static bool InstallMacHook()
    {
        const bool ok = IsHooked<Raw::PlayerSystem::OnPlayerSpawned>() || HookAfter<Raw::PlayerSystem::OnPlayerSpawned>(&OnPlayerSpawned);
        MacHooks::LogInstalled("PlayerSpawnedHook PlayerSystem::OnPlayerSpawned", Raw::PlayerSystem::OnPlayerSpawned.GetOriginalAddress(), ok);
        return ok;
    }

protected:
    bool OnActivateHook() override
    {
        return true;
    }

    bool OnDeactivateHook() override
    {
        return true;
    }
#else
    bool OnActivateHook() override
    {
        return IsHooked<Raw::PlayerSystem::OnPlayerSpawned>() || HookAfter<Raw::PlayerSystem::OnPlayerSpawned>(&OnPlayerSpawned);
    }

    bool OnDeactivateHook() override
    {
        return !IsHooked<Raw::PlayerSystem::OnPlayerSpawned>() || Unhook<Raw::PlayerSystem::OnPlayerSpawned>();
    }
#endif

    inline static void OnPlayerSpawned()
    {
        MAC_HOOK_ENTER("PlayerSystem_OnPlayerSpawned");
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
