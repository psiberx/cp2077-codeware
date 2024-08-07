#pragma once

#include "App/Callback/CallbackSystem.hpp"
#include "App/Callback/CallbackSystemController.hpp"
#include "App/Callback/Events/EntityLifecycleEvent.hpp"
#include "Core/Hooking/HookingAgent.hpp"
#include "Red/Entity.hpp"

namespace App
{
class EntityReassembleHook
    : public CallbackSystemController
    , public Core::HookingAgent
{
public:
    constexpr static auto EventName = Red::CName("Entity/Reassemble");

    Core::Map<Red::CName, Red::CName> GetEvents() override
    {
        return {{EventName, Red::GetTypeName<EntityLifecycleEvent>()}};
    }

protected:
    bool OnActivateHook() override
    {
        return IsHooked<Raw::Entity::Reassemble>() || HookBefore<Raw::Entity::Reassemble>(&OnReassemble);
    }

    bool OnDeactivateHook() override
    {
        return !IsHooked<Raw::Entity::Reassemble>() || Unhook<Raw::Entity::Reassemble>();
    }

    inline static void OnReassemble(Red::Entity* aEntity, uintptr_t, uint64_t, uint64_t,
                                    Red::DynArray<Red::Handle<Red::IComponent>>& aNewComponents,
                                    Red::Handle<Red::ent::EntityParametersStorage>& aEntityParams)
    {
        auto storage = Raw::Entity::ComponentsStorage(aEntity);
        auto compCount = storage->components.size;

        CallbackSystem::Get()->DispatchNativeEvent<EntityLifecycleEvent>(EventName, Red::AsWeakHandle(aEntity));

        if (compCount != storage->components.size)
        {
            while (compCount < storage->components.size)
            {
                aNewComponents.PushBack(storage->components[compCount]);
                ++compCount;
            }
        }
    }
};
}
