#pragma once

#include "App/Scripting/CallbackSystem.hpp"
#include "App/Scripting/EventController.hpp"
#include "Core/Hooking/HookingAgent.hpp"
#include "Red/Entity.hpp"

namespace App
{
class EntityReassembleHook
    : public EventController
    , public Core::HookingAgent
{
public:
    constexpr static auto ReassembleEvent = Red::CName("Entity/Reassemble");

    Core::Vector<Red::CName> GetEvents() override
    {
        return {ReassembleEvent};
    }

    bool Initialize() override
    {
        return IsHooked<Raw::Entity::Reassemble>()
            || HookBefore<Raw::Entity::Reassemble>(&Reassemble);
    }

    bool Uninitialize() override
    {
        return !IsHooked<Raw::Entity::Reassemble>()
            || Unhook<Raw::Entity::Reassemble>();
    }

protected:
    inline static void Reassemble(Red::Entity* aEntity, uintptr_t, uint64_t, uint64_t,
                                  Red::DynArray<Red::Handle<Red::IComponent>>& aNewComponents,
                                  Red::Handle<Red::ent::EntityParametersStorage>& aEntityParams)
    {
        auto storage = Core::OffsetPtr<Red::ent::ComponentsStorage>(aEntity, 0x70);
        auto compCount = storage->components.size;

        CallbackSystem::PassEvent(ReassembleEvent, Red::AsWeakHandle(aEntity));

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
