#pragma once

#include "App/Callback/CallbackSystem.hpp"
#include "App/Callback/CallbackSystemController.hpp"
#include "App/Callback/MacHooks.hpp"
#include "App/Callback/Events/EntityLifecycleEvent.hpp"
#include "Core/Hooking/HookingAgent.hpp"
#include "Red/Entity.hpp"

namespace App
{
class EntityUninitializeHook
    : public CallbackSystemController
    , public Core::HookingAgent
{
public:
    constexpr static auto EventName = Red::CName("Entity/Uninitialize");

    Core::Map<Red::CName, Red::CName> GetEvents() override
    {
        return {{EventName, Red::GetTypeName<EntityLifecycleEvent>()}};
    }

protected:
#if defined(__APPLE__)
    // R18. The hooks are installed once at plugin load (InstallMacCallbackHooks); activation has nothing to do.
public:
    static bool InstallMacHook()
    {
        const bool ok = (IsHooked<Raw::Entity::Uninitialize>() || HookBefore<Raw::Entity::Uninitialize>(&OnUninitialize))
            && (IsHooked<Raw::Entity::Dispose>() || HookBefore<Raw::Entity::Dispose>(&OnDispose));
        MacHooks::LogInstalled("EntityUninitializeHook Entity::Uninitialize", Raw::Entity::Uninitialize.GetOriginalAddress(), ok);
        MacHooks::LogInstalled("EntityUninitializeHook Entity::Dispose", Raw::Entity::Dispose.GetOriginalAddress(), ok);
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
        return (IsHooked<Raw::Entity::Uninitialize>() || HookBefore<Raw::Entity::Uninitialize>(&OnUninitialize))
            && (IsHooked<Raw::Entity::Dispose>() || HookBefore<Raw::Entity::Dispose>(&OnDispose));
    }

    bool OnDeactivateHook() override
    {
        return (!IsHooked<Raw::Entity::Uninitialize>() || Unhook<Raw::Entity::Uninitialize>())
            && (!IsHooked<Raw::Entity::Dispose>() || Unhook<Raw::Entity::Dispose>());
    }
#endif

    inline static void OnUninitialize(Red::Entity* aEntity)
    {
        MAC_HOOK_ENTER("Entity_Uninitialize");
        CallbackSystem::Get()->DispatchNativeEvent<EntityLifecycleEvent>(EventName, Red::AsWeakHandle(aEntity));
    }

    inline static void OnDispose(Red::Entity* aEntity)
    {
        MAC_HOOK_ENTER("Entity_Dispose");
        const auto scene = Raw::Entity::Scene(aEntity);
        const auto status = Raw::Entity::Status(aEntity);

        if (status < Red::EntityStatus::Uninitializing && !scene)
        {
            CallbackSystem::Get()->DispatchNativeEvent<EntityLifecycleEvent>(EventName, Red::AsWeakHandle(aEntity));
        }
    }
};
}
