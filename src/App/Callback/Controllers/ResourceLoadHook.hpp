#pragma once

#include "App/Callback/CallbackSystem.hpp"
#include "App/Callback/CallbackSystemController.hpp"
#include "App/Callback/Events/ResourceEvent.hpp"
#include "Core/Hooking/HookingAgent.hpp"
#include "Red/Serialization.hpp"

namespace App
{
class ResourceLoadHook
    : public CallbackSystemController
    , public Core::HookingAgent
{
public:
    constexpr static auto EventName = Red::CName("Resource/Load");
    constexpr static auto DeprecatedEventName = Red::CName("Resource/Loaded");

    Core::Map<Red::CName, Red::CName> GetEvents() override
    {
        return {{EventName, Red::GetTypeName<ResourceEvent>()}};
    }

    Core::Map<Red::CName, Red::CName> GetMappings() override
    {
        return {{DeprecatedEventName, EventName}};
    }

protected:
    bool OnActivateHook() override
    {
        return IsHooked<Raw::ResourceSerializer::OnDependenciesReady>() ||
               HookBefore<Raw::ResourceSerializer::OnDependenciesReady>(&OnDependenciesReady);
    }

    bool OnDeactivateHook() override
    {
        return !IsHooked<Raw::ResourceSerializer::OnDependenciesReady>() ||
               Unhook<Raw::ResourceSerializer::OnDependenciesReady>();
    }

    inline static void OnDependenciesReady(Red::ResourceSerializer* aSerializer)
    {
        if (aSerializer->serializables.size > 0)
        {
            for (const auto& serializable : aSerializer->serializables)
            {
                if (const auto& resource = Red::Cast<Red::CResource>(serializable))
                {
                    CallbackSystem::Get()->DispatchNativeEvent<ResourceEvent>(EventName, resource);
                }
            }
        }
    }
};
}
