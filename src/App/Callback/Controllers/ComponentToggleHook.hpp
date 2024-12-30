#pragma once

#include "App/Callback/CallbackSystem.hpp"
#include "App/Callback/CallbackSystemController.hpp"
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
    bool OnActivateHook() override
    {
        return IsHooked<Raw::IComponent::Toggle>() || HookAfter<Raw::IComponent::Toggle>(&OnToggleComponent);
    }

    bool OnDeactivateHook() override
    {
        return !IsHooked<Raw::IComponent::Toggle>() || Unhook<Raw::IComponent::Toggle>();
    }

    inline static void OnToggleComponent(Red::IComponent* aComponent, bool aEnabled)
    {
        if (aComponent->owner)
        {
            CallbackSystem::Get()->DispatchNativeEvent<EntityComponentEvent>(
                EventName, Red::AsWeakHandle(aComponent->owner), Red::AsWeakHandle(aComponent));
        }
    }
};
}
