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

    Core::Map<Red::CName, Red::CName> GetEvents() override
    {
        return {{EventName, Red::GetTypeName<ResourceEvent>()}};
    }

protected:
    bool OnActivateHook() override
    {
        return IsHooked<Raw::Serializer::OnDependenciesReady>() || HookBefore<Raw::Serializer::OnDependenciesReady>(&OnDependenciesReady);
    }

    bool OnDeactivateHook() override
    {
        return !IsHooked<Raw::Serializer::OnDependenciesReady>() || Unhook<Raw::Serializer::OnDependenciesReady>();
    }

    inline static void OnDependenciesReady(Red::Serializer* aSerializer)
    {
        if (aSerializer->serializables.size > 0)
        {
            for (const auto& serializable : aSerializer->serializables)
            {
                if (const auto& resource = Red::Cast<Red::CResource>(serializable))
                {
                    CallbackSystem::PassEvent<ResourceEvent>(EventName, resource);
                }
            }
        }
    }
};
}
