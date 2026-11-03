#pragma once

#include "App/Callback/CallbackSystem.hpp"
#include "App/Callback/CallbackSystemController.hpp"
#include "App/Callback/MacHooks.hpp"
#if defined(__APPLE__)
#include <atomic>
#include <cstring>
#include "MacDiag.hpp"
#endif
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

#if defined(__APPLE__)
    // R18. RequestComponents (0xC95E24) is identified but has no caller on Mac: clang inlined it into Initialize and Reassemble,
    // so a hook on it never fires. Entity/Initialize and Entity/Reassemble come from entry hooks on those two functions
    // instead. They run before the game's own setup of the entity, so they set what Windows has set by then (the entity ID,
    // the new appearance name). Installed once at plugin load.
public:
    static bool InstallMacHook()
    {
        const bool initOk = IsHooked<Raw::Entity::Initialize>() || HookBefore<Raw::Entity::Initialize>(&OnMacInitialize);
        MacHooks::LogInstalled("EntityRequestComponentsHook Entity::Initialize", Raw::Entity::Initialize.GetOriginalAddress(),
                               initOk);
        const bool reassembleOk =
            IsHooked<Raw::Entity::Reassemble>() || HookBefore<Raw::Entity::Reassemble>(&OnMacReassemble);
        MacHooks::LogInstalled("EntityRequestComponentsHook Entity::Reassemble",
                               Raw::Entity::Reassemble.GetOriginalAddress(), reassembleOk);
        return initOk && reassembleOk;
    }

protected:
    // Windows installs its hooks when the first Entity/Initialize or Entity/Reassemble callback is registered. The Mac hooks
    // are always installed, so the handlers do nothing until then (the record ID fix is part of that).
    bool OnActivateHook() override
    {
        s_macActive.store(true);
        return true;
    }

    bool OnDeactivateHook() override
    {
        s_macActive.store(false);
        return true;
    }

    inline static std::atomic<bool> s_macActive{false};

    // Resolves the record ID of a puppet or vehicle that was created without one (Windows: the same call with an out pointer).
    // The Mac function returns the ID in x0 and 0 when the parameter is null or holds no record; the game's own setter ignores
    // an ID without a length byte, and so does this.
    inline static void ResolveMacRecordID(Red::Entity* aEntity, Red::EntityInitializeRequest* aRequest)
    {
        if (!aRequest->populationParam)
            return;

        const bool puppet = Red::Cast<Red::gamePuppetBase>(aEntity) != nullptr;
        const bool vehicle = !puppet && Red::Cast<Red::vehicleBaseObject>(aEntity) != nullptr;
        if (!puppet && !vehicle)
            return;

        const uint64_t id = Raw::Entity::ResolveRecordID(aEntity, aRequest->populationParam);
        if (static_cast<uint32_t>(id) == 0 || ((id >> 32) & 0xFF) == 0)
            return;

        Red::TweakDBID recordId{};
        std::memcpy(&recordId, &id, sizeof(recordId));
        if (puppet)
        {
            Raw::Puppet::RecordID::Set(aEntity, recordId);
        }
        else
        {
            Raw::Vehicle::RecordID::Ref(aEntity) = recordId;
        }
        MAC_DIAG( "[cw] R18 ResolveRecordID %s id=0x%llx\n", puppet ? "puppet" : "vehicle",
                     static_cast<unsigned long long>(id));
    }

    inline static void OnMacInitialize(Red::Entity* aEntity, Red::JobQueue&, Red::EntityInitializeRequest* aRequest)
    {
        MAC_HOOK_ENTER("Entity_Initialize");
        if (!s_macActive.load())
            return;

        ResolveMacRecordID(aEntity, aRequest);

        // The game stores the ID itself, but only after this hook. Windows dispatches after that store.
        if (aRequest->entityID)
        {
            Raw::Entity::EntityID::Set(aEntity, aRequest->entityID);
        }

        CallbackSystem::Get()->DispatchNativeEvent<EntityLifecycleEvent>(InitializeEventName, Red::AsWeakHandle(aEntity));
    }

    inline static void OnMacReassemble(Red::Entity* aEntity, uintptr_t a2, Red::CName aNewAppearance, uint64_t a4,
                                       Red::DynArray<Red::Handle<Red::IComponent>>& aNewComponents,
                                       Red::Handle<Red::ent::EntityParametersStorage>& aEntityParams)
    {
        MAC_HOOK_ENTER("Entity_Reassemble");
        if (!s_macActive.load())
            return;

        // The game sets the new appearance first thing; callbacks expect to see it.
        aEntity->appearanceName = aNewAppearance;

        auto compCount = aEntity->components.Size();

        CallbackSystem::Get()->DispatchNativeEvent<EntityLifecycleEvent>(ReassembleEventName, Red::AsWeakHandle(aEntity));

        // Components that callbacks added to the entity are processed with the new ones.
        while (compCount < aEntity->components.Size())
        {
            aNewComponents.PushBack(aEntity->components[compCount]);
            ++compCount;
        }
    }
#else
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
            auto compCount = aEntity->components.Size();

            CallbackSystem::Get()->DispatchNativeEvent<EntityLifecycleEvent>(ReassembleEventName, Red::AsWeakHandle(aEntity));

            if (compCount != aEntity->components.Size())
            {
                while (compCount < aEntity->components.Size())
                {
                    aComponents->PushBack(aEntity->components[compCount]);
                    ++compCount;
                }
            }
        }
    }
#endif
};
}
