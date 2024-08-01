#include "LocalizationService.hpp"
#include "App/Localization/Language.hpp"
#include "Red/Localization.hpp"

void App::LocalizationService::OnBootstrap()
{
    HookAfter<Raw::Localization::LoadTexts>(&LocalizationService::OnLoadTexts).OrThrow();
}

void App::LocalizationService::OnLoadTexts(Red::Handle<Red::localizationPersistenceOnScreenEntries>& aOnScreens,
                                           Red::ResourcePath aPath)
{
    const auto language = Language::ResolveFromTextResource(aPath);

    if (language.IsNone())
        return;

    auto providerBaseType = Red::GetClass<"Codeware.Localization.ModLocalizationProvider">();

    if (!providerBaseType)
        return;

    Red::DynArray<Red::CClass*> providerTypes;
    Red::CRTTISystem::Get()->GetClasses(providerBaseType, providerTypes);

    if (providerTypes.size == 0)
        return;

    Red::DynArray<Red::localizationPersistenceOnScreenEntry> modTextEntries;

    for (auto providerType : providerTypes)
    {
        if (providerType->flags.isAbstract)
            continue;

        auto provider = Red::MakeScriptedHandle<Red::IScriptable>(providerType);

        Red::CallVirtual(provider, "GetOnScreenEntries", language, modTextEntries);
    }

    if (modTextEntries.size == 0)
        return;

    auto& finalTextEntries = aOnScreens->entries;
    Core::Map<uint64_t, uint32_t> textEntryKeyMap;

    for (uint32_t i = 0; i < finalTextEntries.size; ++i)
    {
        auto& textEntry = finalTextEntries[i];

        textEntryKeyMap[textEntry.primaryKey] = i;

        if (textEntry.secondaryKey.Length() > 0)
        {
            textEntryKeyMap[Red::FNV1a32(textEntry.secondaryKey.c_str())] = i;
            textEntryKeyMap[Red::FNV1a64(textEntry.secondaryKey.c_str())] = i;
        }
    }

    for (auto& textEntry : modTextEntries)
    {
        if (textEntry.secondaryKey.Length() == 0)
            continue;

        textEntry.primaryKey = Red::FNV1a32(textEntry.secondaryKey.c_str());
        MergeTextEntry(finalTextEntries, textEntry, textEntryKeyMap);

        textEntry.primaryKey = Red::FNV1a64(textEntry.secondaryKey.c_str());
        MergeTextEntry(finalTextEntries, textEntry, textEntryKeyMap);
    }
}

void App::LocalizationService::MergeTextEntry(Red::DynArray<Red::localizationPersistenceOnScreenEntry>& aFinalList,
                                              Red::localizationPersistenceOnScreenEntry& aTextEntry,
                                              Core::Map<uint64_t, uint32_t>& aTextEntryKeyMap)
{
    const auto& it = aTextEntryKeyMap.find(aTextEntry.primaryKey);
    if (it == aTextEntryKeyMap.end())
    {
        aTextEntryKeyMap.emplace(aTextEntry.primaryKey, aFinalList.size);
        aFinalList.EmplaceBack(aTextEntry);
    }
    else
    {
        auto* existingEntry = aFinalList.Begin() + it.value();
        existingEntry->femaleVariant = aTextEntry.femaleVariant;
        existingEntry->maleVariant = aTextEntry.maleVariant;
    }
}
