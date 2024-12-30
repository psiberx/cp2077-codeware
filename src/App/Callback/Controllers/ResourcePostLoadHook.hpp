#pragma once

#include "App/Callback/CallbackSystem.hpp"
#include "App/Callback/CallbackSystemController.hpp"
#include "App/Callback/Events/ResourceEvent.hpp"
#include "Core/Hooking/HookingAgent.hpp"
#include "Red/Serialization.hpp"

namespace App
{
class ResourcePostLoadHook
    : public CallbackSystemController
    , public Core::HookingAgent
{
public:
    constexpr static auto EventName = Red::CName("Resource/PostLoad");
    constexpr static auto DeprecatedEventName = Red::CName("Resource/Ready");

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
        return IsHooked<Raw::ResourceSerializer::OnResourceReady>() ||
               HookBefore<Raw::ResourceSerializer::OnResourceReady>(&OnResourceReady);
    }

    bool OnDeactivateHook() override
    {
        return !IsHooked<Raw::ResourceSerializer::OnResourceReady>() ||
               Unhook<Raw::ResourceSerializer::OnResourceReady>();
    }

    inline static void OnResourceReady(Red::ResourceSerializer* aSerializer)
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
