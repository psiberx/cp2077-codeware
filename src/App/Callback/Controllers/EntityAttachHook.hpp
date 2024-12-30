#pragma once

#include "App/Callback/CallbackSystem.hpp"
#include "App/Callback/CallbackSystemController.hpp"
#include "App/Callback/Events/EntityLifecycleEvent.hpp"
#include "Core/Hooking/HookingAgent.hpp"
#include "Red/Entity.hpp"

namespace App
{
class EntityAttachHook
    : public CallbackSystemController
    , public Core::HookingAgent
{
public:
    constexpr static auto EventName = Red::CName("Entity/Attach");
    constexpr static auto PostEventName = Red::CName("Entity/AfterAttach");
    constexpr static auto DeprecatedPostEventName = Red::CName("Entity/Attached");

    Core::Map<Red::CName, Red::CName> GetEvents() override
    {
        return {
            {EventName, Red::GetTypeName<EntityLifecycleEvent>()},
            {PostEventName, Red::GetTypeName<EntityLifecycleEvent>()},
        };
    }

    Core::Map<Red::CName, Red::CName> GetMappings() override
    {
        return {
            {DeprecatedPostEventName, PostEventName},
        };
    }

protected:
    bool OnActivateHook() override
    {
        return IsHooked<Raw::Entity::Attach>() || Hook<Raw::Entity::Attach>(&OnAttach);
    }

    bool OnDeactivateHook() override
    {
        return !IsHooked<Raw::Entity::Attach>() || Unhook<Raw::Entity::Attach>();
    }

    inline static void OnAttach(Red::Entity* aEntity, uintptr_t a2)
    {
        CallbackSystem::Get()->DispatchNativeEvent<EntityLifecycleEvent>(EventName, Red::AsWeakHandle(aEntity));

        Raw::Entity::Attach(aEntity, a2);

        CallbackSystem::Get()->DispatchNativeEvent<EntityLifecycleEvent>(PostEventName, Red::AsWeakHandle(aEntity));
    }
};
}
