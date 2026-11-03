#pragma once

#include "App/Callback/CallbackSystem.hpp"
#include "App/Callback/CallbackSystemController.hpp"
#include "App/Callback/MacHooks.hpp"
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
#if defined(__APPLE__)
    // R18. The hooks are installed once at plugin load (InstallMacCallbackHooks); activation has nothing to do.
public:
    static bool InstallMacHook()
    {
        const bool ok = IsHooked<Raw::Entity::Assemble>() || HookAfter<Raw::Entity::Assemble>(&OnAssemble);
        MacHooks::LogInstalled("EntityAssembleHook Entity::Assemble", Raw::Entity::Assemble.GetOriginalAddress(), ok);
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
        return IsHooked<Raw::Entity::Assemble>() || HookAfter<Raw::Entity::Assemble>(&OnAssemble);
    }

    bool OnDeactivateHook() override
    {
        return !IsHooked<Raw::Entity::Assemble>() || Unhook<Raw::Entity::Assemble>();
    }
#endif

    inline static void OnAssemble(Red::Entity* aEntity, uintptr_t)
    {
        MAC_HOOK_ENTER("Entity_Assemble");
        CallbackSystem::Get()->DispatchNativeEvent<EntityLifecycleEvent>(EventName, Red::AsWeakHandle(aEntity));
    }
};
}
