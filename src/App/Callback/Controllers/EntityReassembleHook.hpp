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

    inline static void OnReassemble(Red::Entity* aEntity, uintptr_t a2, Red::CName aNewAppearance, uint64_t a4,
                                    Red::DynArray<Red::Handle<Red::IComponent>>& aNewComponents,
                                    Red::Handle<Red::ent::EntityParametersStorage>& aEntityParams)
    {
        aEntity->appearanceName = aNewAppearance;

        auto compCount = aEntity->components.size;

        CallbackSystem::Get()->DispatchNativeEvent<EntityLifecycleEvent>(EventName, Red::AsWeakHandle(aEntity));

        if (compCount != aEntity->components.size)
        {
            while (compCount < aEntity->components.size)
            {
                aNewComponents.PushBack(aEntity->components[compCount]);
                ++compCount;
            }
        }
    }
};
}
