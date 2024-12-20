#pragma once

#include "App/Callback/CallbackSystem.hpp"
#include "App/Callback/CallbackSystemController.hpp"
#include "App/Callback/Events/EntityLifecycleEvent.hpp"
#include "Core/Hooking/HookingAgent.hpp"
#include "Red/Entity.hpp"
#include "Red/Puppet.hpp"
#include "Red/Vehicle.hpp"

namespace App
{
class EntityRequestComponentsHook
    : public CallbackSystemController
    , public Core::HookingAgent
{
public:
    constexpr static auto InitializeEventName = Red::CName("Entity/Initialize");
    constexpr static auto ReassembleEventName = Red::CName("Entity/Reassemble");

    Core::Map<Red::CName, Red::CName> GetEvents() override
    {
        return {
            {InitializeEventName, Red::GetTypeName<EntityLifecycleEvent>()},
            {ReassembleEventName, Red::GetTypeName<EntityLifecycleEvent>()},
        };
    }

protected:
    bool OnActivateHook() override
    {
        return (IsHooked<Raw::Entity::Initialize>() || HookBefore<Raw::Entity::Initialize>(&OnInitialize))
            && (IsHooked<Raw::Entity::RequestComponents>() || HookBefore<Raw::Entity::RequestComponents>(&OnRequestComponents));
    }

    bool OnDeactivateHook() override
    {
        return (!IsHooked<Raw::Entity::Initialize>() || Unhook<Raw::Entity::Initialize>())
            && (!IsHooked<Raw::Entity::RequestComponents>() || Unhook<Raw::Entity::RequestComponents>());
    }

    inline static void OnInitialize(Red::Entity* aEntity, Red::JobQueue& aJobQueue,
                                    Red::EntityInitializeRequest* aRequest)
    {
        if (auto puppet = Red::Cast<Red::gamePuppetBase>(aEntity))
        {
            Raw::Entity::ResolveRecordID(aEntity, Raw::Puppet::RecordID::Ref(aEntity), aRequest->populationParam);
        }
        else if (auto vehicle = Red::Cast<Red::vehicleBaseObject>(aEntity))
        {
            Raw::Entity::ResolveRecordID(aEntity, Raw::Vehicle::RecordID::Ref(aEntity), aRequest->populationParam);
        }
    }

    inline static void OnRequestComponents(Red::Entity* aEntity, uintptr_t a2,
                                           Red::DynArray<Red::Handle<Red::IComponent>>* aComponents)
    {
        if (aComponents == &aEntity->components)
        {
            CallbackSystem::Get()->DispatchNativeEvent<EntityLifecycleEvent>(InitializeEventName, Red::AsWeakHandle(aEntity));
        }
        else
        {
            auto compCount = aEntity->components.size;

            CallbackSystem::Get()->DispatchNativeEvent<EntityLifecycleEvent>(ReassembleEventName, Red::AsWeakHandle(aEntity));

            if (compCount != aEntity->components.size)
            {
                while (compCount < aEntity->components.size)
                {
                    aComponents->PushBack(aEntity->components[compCount]);
                    ++compCount;
                }
            }
        }
    }
};
}
