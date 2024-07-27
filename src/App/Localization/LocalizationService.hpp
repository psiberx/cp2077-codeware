#pragma once

#include "Core/Foundation/Feature.hpp"
#include "Core/Hooking/HookingAgent.hpp"
#include "Core/Logging/LoggingAgent.hpp"

namespace App
{
class LocalizationService
    : public Core::Feature
    , public Core::HookingAgent
    , public Core::LoggingAgent
{
protected:
    void OnBootstrap() override;

    static void OnLoadTexts(Red::Handle<Red::localizationPersistenceOnScreenEntries>& aOnScreens,
                            Red::ResourcePath aPath);

    static void MergeTextEntry(Red::DynArray<Red::localizationPersistenceOnScreenEntry>& aFinalList,
                               Red::localizationPersistenceOnScreenEntry& aTextEntry,
                               Core::Map<uint64_t, uint32_t>& aTextEntryKeyMap);
};
}
