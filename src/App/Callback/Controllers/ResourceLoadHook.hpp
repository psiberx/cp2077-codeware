#pragma once

#include "App/Callback/CallbackSystem.hpp"
#include "App/Callback/CallbackSystemController.hpp"
#include "App/Callback/Events/ResourceEvent.hpp"
#include "App/Callback/MacHooks.hpp"
#if defined(__APPLE__)
#include "MacDiag.hpp"
#endif
#include "App/Depot/SoundBanksJson.hpp"
#if defined(__APPLE__)
#include "App/Callback/Controllers/MacResourceJob.hpp"
#endif
#include "Core/Hooking/HookingAgent.hpp"
#include "Red/AudioSystem.hpp"
#include "Red/Serialization.hpp"

namespace App
{
class ResourceLoadHook
    : public CallbackSystemController
    , public Core::HookingAgent
{
public:
    constexpr static auto EventName = Red::CName("Resource/Load");
    constexpr static auto DeprecatedEventName = Red::CName("Resource/Loaded");

    Core::Map<Red::CName, Red::CName> GetEvents() override
    {
        return {{EventName, Red::GetTypeName<ResourceEvent>()}};
    }

    Core::Map<Red::CName, Red::CName> GetMappings() override
    {
        return {{DeprecatedEventName, EventName}};
    }

#if defined(__APPLE__)
    // R13. Hooks job 0x2257548 once, at plugin load. HookBefore runs the callback, then the original.
    // R18. The soundbanks half: HookAfter on SoundBankManager::ReadSoundBanksJson (0xDC8D0C), the body, not its wrapper.
    static bool InstallMacHook()
    {
        const bool ok = IsHooked<Raw::ResourceSerializer::MacLoadJob>() ||
                        HookBefore<Raw::ResourceSerializer::MacLoadJob>(&OnMacLoadJob);
        MAC_DIAG_UNLESS(ok, "[cw] hook %s ResourceLoadHook target=%p\n", ok ? "installed" : "FAILED",
                     reinterpret_cast<void*>(Raw::ResourceSerializer::MacLoadJob.GetOriginalAddress()));
        const bool soundOk = IsHooked<Raw::SoundBankManager::ReadSoundBanksJson>() ||
                             HookAfter<Raw::SoundBankManager::ReadSoundBanksJson>(&OnReadSoundBanksJson);
        MacHooks::LogInstalled("ResourceLoadHook SoundBankManager::ReadSoundBanksJson",
                               Raw::SoundBankManager::ReadSoundBanksJson.GetOriginalAddress(), soundOk);
        return ok && soundOk;
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

    inline static void OnMacLoadJob(Red::ResourceSerializer** aCaptures, void*)
    {
        DispatchMacResourceJob(aCaptures, EventName, MacHookStats::load, true);
    }
#else
    bool OnActivateHook() override
    {
        return (IsHooked<Raw::ResourceSerializer::SchedulePostLoadJobs>() ||
                HookBefore<Raw::ResourceSerializer::SchedulePostLoadJobs>(&OnSchedulePostLoadJobs)) &&
               (IsHooked<Raw::SoundBankManager::ReadSoundBanksJson>() ||
                HookAfter<Raw::SoundBankManager::ReadSoundBanksJson>(&OnReadSoundBanksJson));
    }

    bool OnDeactivateHook() override
    {
        return (!IsHooked<Raw::ResourceSerializer::SchedulePostLoadJobs>() ||
                Unhook<Raw::ResourceSerializer::SchedulePostLoadJobs>()) &&
               (!IsHooked<Raw::SoundBankManager::ReadSoundBanksJson>() ||
                Unhook<Raw::SoundBankManager::ReadSoundBanksJson>());
    }

    inline static void OnSchedulePostLoadJobs(uint64_t a1, uint8_t a2, uint64_t a3, uint64_t a4,
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

    inline static void OnReadSoundBanksJson(void* aManager)
    {
        MAC_HOOK_ENTER("SoundBankManager_ReadSoundBanksJson");
#if defined(__APPLE__)
        // Building the resource costs a copy of every registered bank. Nothing to do without a Resource/Load callback.
        if (!CallbackSystem::Get()->HasCallbacks(EventName))
            return;
#endif
        auto& registeredBanks = Red::SoundBankManager::RegisteredBanks::Ref(aManager);

        auto resource = Red::MakeHandle<SoundBanksJson>();
        resource->path = R"(base\sound\event\soundbanks.json)";
        resource->soundBanks.Reserve(registeredBanks.size);

        registeredBanks.ForEach([&resource](const Red::CName& aName, Red::SharedPtr<Red::SoundBankEntry>& aEntry) {
            resource->soundBanks.EmplaceBack(*aEntry);
        });

        const bool dispatched = CallbackSystem::Get()->DispatchNativeEvent<ResourceEvent>(EventName, resource);
#if defined(__APPLE__)
        MAC_DIAG("[diag] R18 soundbanks: %u registered banks copied, Resource/Load dispatched=%d\n",
                 static_cast<unsigned>(resource->soundBanks.Size()), dispatched ? 1 : 0);
#endif
        if (dispatched)
        {
            for (auto& resourceEntry : resource->soundBanks)
            {
                if (auto existingEntry = registeredBanks.Get(resourceEntry.name))
                {
                    **existingEntry = resourceEntry;
                }
                else
                {
                    registeredBanks.Insert(resourceEntry.name, Red::MakeShared<Red::SoundBankEntry>(resourceEntry));
                }
            }
        }
    }
};
}
