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
        return (IsHooked<Raw::ResourceSerializer::OnDependenciesReady>() ||
                HookBefore<Raw::ResourceSerializer::OnDependenciesReady>(&OnDependenciesReady)) &&
               (IsHooked<Raw::SoundBankManager::ReadSoundBanksJson>() ||
                HookAfter<Raw::SoundBankManager::ReadSoundBanksJson>(&OnReadSoundBanksJson));
    }

    bool OnDeactivateHook() override
    {
        return (!IsHooked<Raw::ResourceSerializer::OnDependenciesReady>() ||
                Unhook<Raw::ResourceSerializer::OnDependenciesReady>()) &&
               (!IsHooked<Raw::SoundBankManager::ReadSoundBanksJson>() ||
                Unhook<Raw::SoundBankManager::ReadSoundBanksJson>());
    }

    inline static void OnDependenciesReady(Red::ResourceSerializer* aSerializer)
    {
        if (aSerializer->serializables.size > 0)
        {
            for (const auto& serializable : aSerializer->serializables)
            {
                if (const auto& resource = Red::Cast<Red::CResource>(serializable))
                {
                    CallbackSystem::Get()->DispatchNativeEvent<ResourceEvent>(EventName, resource);
                }
            }
        }
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
