#pragma once

#include "App/Callback/CallbackSystem.hpp"
#include "App/Callback/CallbackSystemController.hpp"
#include "App/Callback/Events/EntityBuilderEvent.hpp"
#include "Core/Hooking/HookingAgent.hpp"
#include "Red/EntityBuilder.hpp"

namespace App
{
class EntityExtractHook
    : public CallbackSystemController
    , public Core::HookingAgent
{
public:
    constexpr static auto EventName = Red::CName("Entity/Extract");

    Core::Map<Red::CName, Red::CName> GetEvents() override
    {
        return {{EventName, Red::GetTypeName<EntityBuilderEvent>()}};
    }

protected:
    bool OnActivateHook() override
    {
        return IsHooked<Raw::EntityBuilder::ExtractComponentsJob>()
            || HookBefore<Raw::EntityBuilder::ExtractComponentsJob>(&OnExtractComponentsJob);
    }

    bool OnDeactivateHook() override
    {
        return !IsHooked<Raw::EntityBuilder::ExtractComponentsJob>()
            || Unhook<Raw::EntityBuilder::ExtractComponentsJob>();
    }

    inline static void OnExtractComponentsJob(Red::EntityBuilderJobParams* aParams, void*)
    {
        if (!aParams->entityBuilderWeak.Expired())
        {
            CallbackSystem::Get()->DispatchNativeEvent<EntityBuilderEvent>(EventName, aParams->entityBuilderWeak);
        }
    }
};
}
