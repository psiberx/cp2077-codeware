#pragma once

#include "App/Callback/CallbackSystem.hpp"
#include "App/Callback/CallbackSystemController.hpp"
#include "App/Callback/MacHooks.hpp"
#include "App/Callback/Events/EntityComponentEvent.hpp"
#include "Core/Hooking/HookingAgent.hpp"
#include "Red/Entity.hpp"

namespace App
{
class ComponentToggleHook
    : public CallbackSystemController
    , public Core::HookingAgent
{
public:
    constexpr static auto EventName = Red::CName("Component/Toggle");

    Core::Map<Red::CName, Red::CName> GetEvents() override
    {
        return {{EventName, Red::GetTypeName<EntityComponentEvent>()}};
    }

protected:
#if defined(__APPLE__)
    // R18. The hooks are installed once at plugin load (InstallMacCallbackHooks); activation has nothing to do.
public:
    static bool InstallMacHook()
    {
        const bool ok = IsHooked<Raw::IComponent::Toggle>() || HookAfter<Raw::IComponent::Toggle>(&OnToggleComponent);
        MacHooks::LogInstalled("ComponentToggleHook IComponent::Toggle", Raw::IComponent::Toggle.GetOriginalAddress(), ok);
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
        return IsHooked<Raw::IComponent::Toggle>() || HookAfter<Raw::IComponent::Toggle>(&OnToggleComponent);
    }

    bool OnDeactivateHook() override
    {
        return !IsHooked<Raw::IComponent::Toggle>() || Unhook<Raw::IComponent::Toggle>();
    }
#endif

    inline static void OnToggleComponent(Red::IComponent* aComponent, bool aEnabled)
    {
        MAC_HOOK_ENTER("IComponent_Toggle");
        if (aComponent->owner)
        {
            CallbackSystem::Get()->DispatchNativeEvent<EntityComponentEvent>(
                EventName, Red::AsWeakHandle(aComponent->owner), Red::AsWeakHandle(aComponent));
        }
    }
};
}
