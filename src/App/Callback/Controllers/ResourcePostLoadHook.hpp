#pragma once

#include "App/Callback/CallbackSystem.hpp"
#include "App/Callback/CallbackSystemController.hpp"
#include "App/Callback/Events/ResourceEvent.hpp"
#if defined(__APPLE__)
#include "App/Callback/Controllers/MacResourceJob.hpp"
#include "MacDiag.hpp"
#endif
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

#if defined(__APPLE__)
    // R13. Hooks job 0x2257830 once, at plugin load. HookBefore runs the callback, then the original.
    static bool InstallMacHook()
    {
        const bool ok = IsHooked<Raw::ResourceSerializer::MacPostLoadJob>() ||
                        HookBefore<Raw::ResourceSerializer::MacPostLoadJob>(&OnMacPostLoadJob);
        MAC_DIAG_UNLESS(ok, "[cw] hook %s ResourcePostLoadHook target=%p\n", ok ? "installed" : "FAILED",
                     reinterpret_cast<void*>(Raw::ResourceSerializer::MacPostLoadJob.GetOriginalAddress()));
        return ok;
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

    inline static void OnMacPostLoadJob(Red::ResourceSerializer** aCaptures, void*)
    {
        DispatchMacResourceJob(aCaptures, EventName, MacHookStats::postLoad, false);
    }
#else
    bool OnActivateHook() override
    {
        return IsHooked<Raw::ResourceSerializer::ScheduleFinalizeJobs>() ||
               HookBefore<Raw::ResourceSerializer::ScheduleFinalizeJobs>(&OnScheduleFinalizeJobs);
    }

    bool OnDeactivateHook() override
    {
        return !IsHooked<Raw::ResourceSerializer::ScheduleFinalizeJobs>() ||
               Unhook<Raw::ResourceSerializer::ScheduleFinalizeJobs>();
    }

    inline static void OnScheduleFinalizeJobs(uint64_t a1, uint8_t a2, uint64_t a3, uint64_t a4,
                                              Red::ResourceSerializer** aCaptures)
    {
        auto* jobQueue = reinterpret_cast<Red::JobQueue*>(a3 - offsetof(Red::JobQueue, unk10));
        auto* serializer = *aCaptures;

        jobQueue->Dispatch([serializer](const Red::JobGroup& aJobGroup) {
            if (!serializer->serializables.IsEmpty())
            {
                for (const auto& serializable : serializer->serializables)
                {
                    if (const auto& resource = Red::Cast<Red::CResource>(serializable))
                    {
                        CallbackSystem::Get()->DispatchNativeEvent<ResourceEvent>(EventName, resource, aJobGroup);
                    }
                }
            }
        });
    }
#endif
};
}
