#pragma once

#include "App/Callback/CallbackSystem.hpp"
#include "App/Callback/CallbackSystemController.hpp"
#include "App/Callback/Events/EntityLifecycleEvent.hpp"
#if defined(__APPLE__)
#include "App/Callback/MacHookStats.hpp"
#endif
#include "Core/Hooking/HookingAgent.hpp"
#include "Red/Entity.hpp"
#if defined(__APPLE__)
#include "MacEngine.hpp"
#include "Red/Puppet.hpp"
#include "Red/TweakDB.hpp"
#include <atomic>
#include <cstring>
#include "MacDiag.hpp"
#endif

namespace App
{
class EntityAttachHook
    : public CallbackSystemController
    , public Core::HookingAgent
{
public:
    constexpr static auto EventName = Red::CName("Entity/Attach");
    constexpr static auto PostEventName = Red::CName("Entity/AfterAttach");
    constexpr static auto DeprecatedPostEventName = Red::CName("Entity/Attached");

    Core::Map<Red::CName, Red::CName> GetEvents() override
    {
        return {
            {EventName, Red::GetTypeName<EntityLifecycleEvent>()},
            {PostEventName, Red::GetTypeName<EntityLifecycleEvent>()},
        };
    }

    Core::Map<Red::CName, Red::CName> GetMappings() override
    {
        return {
            {DeprecatedPostEventName, PostEventName},
        };
    }

#if defined(__APPLE__)
    // R13. Hooks Entity_Attach (0xC99368) once, at plugin load.
    static bool InstallMacHook()
    {
        const bool ok = IsHooked<Raw::Entity::Attach>() || Hook<Raw::Entity::Attach>(&OnAttach);
        MAC_DIAG_UNLESS(ok, "[cw] hook %s EntityAttachHook target=%p\n", ok ? "installed" : "FAILED",
                     reinterpret_cast<void*>(Raw::Entity::Attach.GetOriginalAddress()));
        return ok;
    }
#endif

#if defined(__APPLE__)
    // SELFTEST R18. Read-only check of Raw::Puppet::RecordID (+0x25C on Mac, found through the twin setter 0x378A7D0) at the
    // first puppet that attaches: the id stored there must be a record that exists in TweakDB. The neighbouring words are logged
    // too, so a wrong offset shows where the id really is. Runs once; reads the entity and TweakDB under its shared lock, the
    // same read the game's own record lookups do.
    inline static void PuppetRecordIdCheck(Red::Entity* aEntity)
    {
        static std::atomic<bool> s_checked{false};
        if (s_checked.load(std::memory_order_relaxed) || !Mac::DiagEnabled())
            return;

        static Red::CClass* s_puppetClass = Red::GetClass<Red::gamePuppetBase>();
        if (!s_puppetClass || !aEntity->GetType()->IsA(s_puppetClass))
            return;

        if (s_checked.exchange(true))
            return;

        const auto base = reinterpret_cast<const uint8_t*>(aEntity);
        for (uintptr_t offset = 0x254; offset <= 0x268; offset += 4)
        {
            Red::TweakDBID id{};
            std::memcpy(&id, base + offset, sizeof(id));
            MAC_DIAG( "[selftest] R18 puppet record id candidate +0x%llx = 0x%016llx exists=%d\n",
                         static_cast<unsigned long long>(offset), static_cast<unsigned long long>(*reinterpret_cast<uint64_t*>(&id)),
                         Red::RecordExists(id) ? 1 : 0);
        }

        const auto id = Raw::Puppet::RecordID::Ref(aEntity);
        const bool exists = Red::RecordExists(id);
        MAC_DIAG( "[selftest] R18 first puppet attach: record id at +0x25C exists in TweakDB=%d\n", exists ? 1 : 0);
        Mac::R18Check(exists, "the puppet record id at +0x25C is a TweakDB record");
    }

#endif

protected:
#if defined(__APPLE__)
    // R13. The hook is already installed at plugin load, so activation has nothing to do.
    bool OnActivateHook() override
    {
        return true;
    }

    bool OnDeactivateHook() override
    {
        return true;
    }
#else
    bool OnActivateHook() override
    {
        return IsHooked<Raw::Entity::Attach>() || Hook<Raw::Entity::Attach>(&OnAttach);
    }

    bool OnDeactivateHook() override
    {
        return !IsHooked<Raw::Entity::Attach>() || Unhook<Raw::Entity::Attach>();
    }
#endif

    inline static void OnAttach(Red::Entity* aEntity, uintptr_t a2)
    {
#if defined(__APPLE__)
        // R13. The hook starts at plugin load, before the CallbackSystem class is registered. Both
        // dispatches wait for the system to exist; the original always runs, even if a dispatch throws.
        MacHookStats::attach.calls.fetch_add(1, std::memory_order_relaxed);
        PuppetRecordIdCheck(aEntity);
        try
        {
            if (CallbackSystem::Exists())
            {
                if (CallbackSystem::Get()->DispatchNativeEvent<EntityLifecycleEvent>(EventName,
                                                                                    Red::AsWeakHandle(aEntity)))
                {
                    MacHookStats::attach.dispatched.fetch_add(1, std::memory_order_relaxed);
                }
            }
            else
            {
                MacHookStats::attach.noSystem.fetch_add(1, std::memory_order_relaxed);
            }
        }
        catch (...)
        {
        }

        Raw::Entity::Attach(aEntity, a2);

        try
        {
            if (CallbackSystem::Exists())
            {
                if (CallbackSystem::Get()->DispatchNativeEvent<EntityLifecycleEvent>(PostEventName,
                                                                                    Red::AsWeakHandle(aEntity)))
                {
                    MacHookStats::attach.dispatched.fetch_add(1, std::memory_order_relaxed);
                }
            }
        }
        catch (...)
        {
        }
#else
        CallbackSystem::Get()->DispatchNativeEvent<EntityLifecycleEvent>(EventName, Red::AsWeakHandle(aEntity));

        Raw::Entity::Attach(aEntity, a2);

        CallbackSystem::Get()->DispatchNativeEvent<EntityLifecycleEvent>(PostEventName, Red::AsWeakHandle(aEntity));
#endif
    }
};
}
