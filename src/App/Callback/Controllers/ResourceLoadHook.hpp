#pragma once

#include "App/Callback/CallbackSystem.hpp"
#include "App/Callback/CallbackSystemController.hpp"
#include "App/Callback/Events/ResourceEvent.hpp"
#include "App/Depot/SoundBanksJson.hpp"
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

protected:
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

    inline static void OnReadSoundBanksJson(void* aManager)
    {
        auto& registeredBanks = Red::SoundBankManager::RegisteredBanks::Ref(aManager);

        auto resource = Red::MakeHandle<SoundBanksJson>();
        resource->path = R"(base\sound\event\soundbanks.json)";
        resource->soundBanks.Reserve(registeredBanks.size);

        registeredBanks.ForEach([&resource](const Red::CName& aName, Red::SharedPtr<Red::SoundBankEntry>& aEntry) {
            resource->soundBanks.EmplaceBack(*aEntry);
        });

        if (CallbackSystem::Get()->DispatchNativeEvent<ResourceEvent>(EventName, resource))
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
