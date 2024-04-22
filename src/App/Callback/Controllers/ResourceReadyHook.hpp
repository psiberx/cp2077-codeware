#pragma once

#include "App/Callback/CallbackSystem.hpp"
#include "App/Callback/CallbackSystemController.hpp"
#include "App/Callback/Events/ResourceEvent.hpp"
#include "Core/Hooking/HookingAgent.hpp"
#include "Red/Serialization.hpp"

namespace App
{
class ResourceReadyHook
    : public CallbackSystemController
    , public Core::HookingAgent
{
public:
    constexpr static auto EventName = Red::CName("Resource/Ready");

    Core::Vector<Red::CName> GetEvents() override
    {
        return {EventName};
    }

protected:
    bool OnActivateHook() override
    {
        return IsHooked<Raw::Serializer::OnResourceReady>() || HookBefore<Raw::Serializer::OnResourceReady>(&OnResourceReady);
    }

    bool OnDeactivateHook() override
    {
        return !IsHooked<Raw::Serializer::OnResourceReady>() || Unhook<Raw::Serializer::OnResourceReady>();
    }

    inline static void OnResourceReady(Red::Serializer* aSerializer)
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
