#pragma once

#include "App/Callback/CallbackSystem.hpp"
#include "App/Callback/CallbackSystemController.hpp"
#include "App/Callback/MacHooks.hpp"
#include "App/Callback/Events/EntityLifecycleEvent.hpp"
#include "Core/Hooking/HookingAgent.hpp"
#include "Red/Entity.hpp"

namespace App
{
class EntityDetachHook
    : public CallbackSystemController
    , public Core::HookingAgent
{
public:
    constexpr static auto EventName = Red::CName("Entity/Detach");

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
        const bool ok = IsHooked<Raw::Entity::Detach>() || HookBefore<Raw::Entity::Detach>(&OnDetach);
        MacHooks::LogInstalled("EntityDetachHook Entity::Detach", Raw::Entity::Detach.GetOriginalAddress(), ok);
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
        return IsHooked<Raw::Entity::Detach>() || HookBefore<Raw::Entity::Detach>(&OnDetach);
    }

    bool OnDeactivateHook() override
    {
        return !IsHooked<Raw::Entity::Detach>() || Unhook<Raw::Entity::Detach>();
    }
#endif

    inline static void OnDetach(Red::Entity* aEntity)
    {
        MAC_HOOK_ENTER("Entity_Detach");
        CallbackSystem::Get()->DispatchNativeEvent<EntityLifecycleEvent>(EventName, Red::AsWeakHandle(aEntity));
    }
};
}
