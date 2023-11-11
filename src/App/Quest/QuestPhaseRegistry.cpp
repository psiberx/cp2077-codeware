#include "QuestPhaseRegistry.hpp"
#include "App/Device/ResetSecuritySystemNetwork.hpp"
#include "App/Quest/QuestPhaseGraphBuilder.hpp"
#include "App/World/DistrictResolver.hpp"
#include "Red/TweakDB.hpp"

namespace
{
constexpr auto MinorActivitiesResource = R"(base\open_world\minor_activities\open_world_minor_activities.questphase)";
}

void App::QuestPhaseRegistry::OnBootstrap()
{
    HookAfter<Raw::QuestLoader::PhasePreloadCheck>(&QuestPhaseRegistry::OnPhasePreloadCheck);
    HookAfter<Raw::QuestPhaseInstance::Initialize>(&QuestPhaseRegistry::OnInitializePhase);
}

void App::QuestPhaseRegistry::OnPhasePreloadCheck(bool& aPreload, void* aLoader, const Red::QuestNodePath& aPhaseNodePath)
{
    if (!aPreload)
    {
        if (s_minorActivitiesRootPhasePath.size == 0)
        {
            auto& nodePathMap = Raw::QuestLoader::NodePathMap::Ref(aLoader);
            auto minorActivitiesPhasePath = nodePathMap.Get(MinorActivitiesResource);

            if (!minorActivitiesPhasePath)
                return;

            s_minorActivitiesRootPhasePath = *minorActivitiesPhasePath;
        }

        if (aPhaseNodePath.size > s_minorActivitiesRootPhasePath.size &&
            std::memcmp(aPhaseNodePath.entries, s_minorActivitiesRootPhasePath.entries,
                        s_minorActivitiesRootPhasePath.size * sizeof(Red::NodeID)) == 0)
        {
            auto& preloadList = Raw::QuestLoader::PreloadList::Ref(aLoader);
            preloadList.PushBack(aPhaseNodePath);

            aPreload = true;
        }
    }
}

void App::QuestPhaseRegistry::OnInitializePhase(Red::questPhaseInstance* aPhase, Red::QuestContext& aContext,
                                               const Red::Handle<Red::questQuestPhaseResource>& aPhaseResource,
                                               Red::Handle<Red::questGraphDefinition>& aPhaseGraph,
                                               const Red::QuestNodePath& aParentPath, Red::NodeID aPhaseNodeID)
{
    if (aParentPath.size == 0 && aPhaseNodeID == 0)
    {
        s_activities.clear();
        s_phaseInstances.clear();
    }

    {
        auto phaseNodeKey = MakePhaseNodeKey(aParentPath, aPhaseNodeID, 0);
        s_phaseInstances[phaseNodeKey] = Red::AsWeakHandle(aPhase);
    }

    if (!aPhaseResource)
        return;

    QuestPhaseGraphAccessor phaseGraphAccessor(aPhaseGraph);
    ApplyActivityBugfixes(phaseGraphAccessor, aPhaseResource, aPhaseGraph);
    RegisterCrimeActivity(phaseGraphAccessor, aPhase, aPhaseResource, aPhaseGraph, aParentPath, aPhaseNodeID);
    // RegisterCyberpsychoActivity(phaseGraphAccessor, aPhase, aPhaseGraph, aParentPath, aPhaseNodeID);
}

void App::QuestPhaseRegistry::ApplyActivityBugfixes(App::QuestPhaseGraphAccessor& aPhaseGraphAccessor,
                                                   const Red::Handle<Red::questQuestPhaseResource>& aPhaseResource,
                                                   Red::Handle<Red::questGraphDefinition>& aPhaseGraph)
{
    if (aPhaseResource->path == R"(base\open_world\minor_activities\badlands\inland_avenue_se1\ma_bls_se1_ina_09\ma_bls_ina_se1_09_phase.questphase)")
    {
        for (auto& prefabNode : aPhaseGraphAccessor.GetNodesOfType<Red::questWorldDataManagerNodeDefinition>())
        {
            if (auto& prefabNodeType = Red::Cast<Red::questShowWorldNode_NodeType>(prefabNode->type))
            {
                prefabNodeType->show = false;
            }
        }
    }
}

bool App::QuestPhaseRegistry::RegisterCrimeActivity(App::QuestPhaseGraphAccessor& aPhaseGraphAccessor,
                                                   Red::questPhaseInstance* aPhase,
                                                   const Red::Handle<Red::questQuestPhaseResource>& aPhaseResource,
                                                   Red::Handle<Red::questGraphDefinition>& aPhaseGraph,
                                                   const Red::QuestNodePath& aParentPath, Red::NodeID aPhaseNodeID)
{
    auto inputNode = aPhaseGraphAccessor.FindInputNode();

    if (!inputNode)
        return false;

    auto poiMappin = aPhaseGraphAccessor.FindCompletedPointOfInterestMappin();

    if (!poiMappin)
        return false;

    auto activityName = ExtractMinorActivityName(poiMappin->path->realPath);

    if (!activityName)
        return false;

    auto communities = aPhaseGraphAccessor.FindCommunities();
    auto spawnSets = aPhaseGraphAccessor.FindSpawnSets();
    auto spawners = aPhaseGraphAccessor.FindSpawners();

    if (communities.empty() && spawnSets.empty() && spawners.empty())
        return false;

    auto activity = Core::MakeShared<ActivityDefinition>();

    activity->name = activityName;
    activity->kind = "ncpd";

    activity->mappinHash = Red::Murmur3_32(poiMappin->path->realPath.c_str());

    {
        auto journalManager = Red::GetGameSystem<Red::gameIJournalManager>();
        Raw::JournalManager::GetEntryByHash(journalManager, activity->mappinEntry, activity->mappinHash);

        if (!activity->mappinEntry)
            return false;

        auto& mappinData = Red::Cast<Red::gamemappinsPhaseVariant>(activity->mappinEntry->mappinData.typedVariant);

        if (!mappinData || !IsCombatActivityVariant(mappinData->variant))
            return false;

        Red::CallGlobal("gameuiMappinUIUtils::MappinToString;gamedataMappinVariant", activity->title, mappinData->variant);
        Red::CallGlobal("gameuiMappinUIUtils::MappinToDescriptionString;gamedataMappinVariant", activity->description, mappinData->variant);
    }

    activity->district = DistrictResolver::GetDistrict(activity->name);
    activity->area = DistrictResolver::GetArea(activity->name);

    for (const auto& community : communities)
    {
        activity->communityRefs.push_back({community->spawnerReference, community->communityEntryName});
    }

    for (const auto& spawnSet : spawnSets)
    {
        activity->communityRefs.push_back({spawnSet->reference, spawnSet->entryName});
    }

    for (const auto& spawner : spawners)
    {
        activity->spawnerRefs.push_back(spawner->spawnerReference);
    }

    for (const auto& event : aPhaseGraphAccessor.FindManagerEvents())
    {
        if (event->PSClassName)
        {
            activity->persistenceRefs.push_back({event->objectRef.reference});
            activity->persistenceRefs.push_back({event->objectRef.reference, event->componentName});
            activity->persistenceRefs.push_back({event->objectRef.reference, "master"});
        }
    }

    for (const auto& journalEntry : aPhaseGraphAccessor.FindJournalEntries())
    {
        if (journalEntry->type->path->className != Red::GetTypeName<Red::gameJournalPointOfInterestMappin>())
        {
            activity->journalHashes.push_back(Red::Murmur3_32(journalEntry->type->path->realPath.c_str()));
        }
    }

    for (const auto& journalObjective : aPhaseGraphAccessor.FindJournalObjectives())
    {
        activity->journalHashes.push_back(Red::Murmur3_32(journalObjective->realPath.c_str()));
    }

    // for (const auto& factChange : aPhaseGraphAccessor.FindFactChanges())
    // {
    //     if (IsMinorActivityRelatedFact(factChange->factName))
    //     {
    //         activity->namedFacts.emplace_back(factChange->factName.c_str());
    //     }
    // }

    for (const auto& graphPath : aPhaseGraphAccessor.GetAllGraphPaths(aParentPath, aPhaseNodeID))
    {
        activity->graphFacts.emplace_back(graphPath);
    }

    for (const auto& lootObjective : aPhaseGraphAccessor.FindLootObjectives())
    {
        activity->lootItemIDs.push_back(lootObjective->itemID);
    }

    if (auto lootContainer = aPhaseGraphAccessor.FindLootContainer())
    {
        activity->lootContainerRef = lootContainer->objectRef;
        activity->persistenceRefs.push_back({lootContainer->objectRef});

        if (activity->lootItemIDs.empty())
        {
            for (const auto& suffix : {"_shard", "_onscreen", "_onscreen_01", "_onscreen_02"})
            {
                Red::TweakDBID readableID(std::string("Items.") + activityName.ToString() + suffix);
                if (Red::RecordExists(readableID))
                {
                    activity->lootItemIDs.push_back(readableID);
                    break;
                }
            }
        }

        {
            QuestPhaseGraphBuilder phaseGraphBuilder{aPhaseGraph};

            {
                auto pauseNode = phaseGraphBuilder.AddStaticEntitySpawnWait(activity->lootContainerRef);
                auto eventNode = phaseGraphBuilder.AddEventDispatch(activity->lootContainerRef);
                eventNode->event = Red::MakeHandle<Red::gameResetContainerEvent>();

                phaseGraphBuilder.AddConnection(inputNode, pauseNode);
                phaseGraphBuilder.AddConnection(pauseNode, eventNode);
            }
        }
    }

    Red::NodeID resetNodeID = 900;

    for (const auto& factChange : aPhaseGraphAccessor.FindFactChanges())
    {
        if (IsMinorActivityRelatedFact(factChange->factName))
        {
            activity->namedFacts.emplace_back(factChange->factName.c_str());

            auto resetNodeType = Red::MakeHandle<Red::questSetVar_NodeType>();
            resetNodeType->factName = factChange->factName;
            resetNodeType->setExactValue = true;
            resetNodeType->value = 0;

            auto resetNode = Red::MakeHandle<Red::questFactsDBManagerNodeDefinition>();
            resetNode->id = ++resetNodeID;
            resetNode->type = resetNodeType;

            activity->resetNodes.push_back(std::move(resetNode));
        }
    }

    if (aPhaseResource->phasePrefabs.size > 0)
    {
        for (const auto& phasePrefab : aPhaseResource->phasePrefabs)
        {
            auto resetNodeType = Red::MakeHandle<Red::questShowWorldNode_NodeType>();
            resetNodeType->objectRef = phasePrefab.prefabNodeRef;
            resetNodeType->show = true;

            auto resetNode = Red::MakeHandle<Red::questWorldDataManagerNodeDefinition>();
            resetNode->id = ++resetNodeID;
            resetNode->type = resetNodeType;

            activity->resetNodes.push_back(std::move(resetNode));
        }
    }

    for (const auto& prefabNode : aPhaseGraphAccessor.GetNodesOfType<Red::questWorldDataManagerNodeDefinition>())
    {
        if (auto& prefabNodeType = Red::Cast<Red::questTogglePrefabVariant_NodeType>(prefabNode->type))
        {
            auto resetNodeType = Red::MakeHandle<Red::questTogglePrefabVariant_NodeType>();
            resetNodeType->params = prefabNodeType->params;
            for (auto& param : resetNodeType->params)
            {
                for (auto& state : param.variantStates)
                {
                    state.show = !state.show;
                }
            }

            auto resetNode = Red::MakeHandle<Red::questWorldDataManagerNodeDefinition>();
            resetNode->id = ++resetNodeID;
            resetNode->type = resetNodeType;

            activity->resetNodes.push_back(std::move(resetNode));
            continue;
        }

        if (auto& prefabNodeType = Red::Cast<Red::questShowWorldNode_NodeType>(prefabNode->type))
        {
            auto resetNodeType = Red::MakeHandle<Red::questShowWorldNode_NodeType>();
            resetNodeType->objectRef = prefabNodeType->objectRef;
            resetNodeType->componentName = prefabNodeType->componentName;
            resetNodeType->isPlayer = prefabNodeType->isPlayer;
            resetNodeType->show = !prefabNodeType->show;

            auto resetNode = Red::MakeHandle<Red::questWorldDataManagerNodeDefinition>();
            resetNode->id = ++resetNodeID;
            resetNode->type = resetNodeType;

            activity->resetNodes.push_back(std::move(resetNode));
        }
    }

    for (const auto& managerNode : aPhaseGraphAccessor.GetNodesOfType<Red::questEventManagerNodeDefinition>())
    {
        if (managerNode->event->GetType()->GetName() == "QuestExecuteTransition")
        {
            auto transition = managerNode->event->GetType()->GetProperty("transition")
                                  ->GetValuePtr<Red::AreaTypeTransition>(managerNode->event.instance);

            if (transition->transitionTo == Red::ESecurityAreaType::DISABLED &&
                transition->transitionMode == Red::ETransitionMode::FORCED)
            {
                auto resetEvent = managerNode->event->GetType()->CreateInstance(true);
                auto resetTransition = managerNode->event->GetType()->GetProperty("transition")
                                  ->GetValuePtr<Red::AreaTypeTransition>(resetEvent);
                resetTransition->transitionTo = Red::ESecurityAreaType::DANGEROUS;
                resetTransition->transitionMode = Red::ETransitionMode::FORCED;

                auto resetNode = Red::MakeHandle<Red::questEventManagerNodeDefinition>();
                resetNode->id = managerNode->id;
                resetNode->event = Red::Handle(reinterpret_cast<Red::IScriptable*>(resetEvent));
                resetNode->objectRef = managerNode->objectRef;
                resetNode->managerName = managerNode->managerName;
                resetNode->componentName = managerNode->componentName;
                resetNode->PSClassName = managerNode->PSClassName;
                resetNode->isObjectPlayer = managerNode->isObjectPlayer;
                resetNode->isUiEvent = managerNode->isUiEvent;

                activity->resetNodes.push_back(std::move(resetNode));
            }
        }
    }

    activity->phaseInstance = aPhase;
    activity->phaseGraph = aPhaseGraph;
    activity->phaseResource = aPhaseResource;
    activity->phaseNodeKey = MakePhaseNodeKey(aParentPath, aPhaseNodeID);
    activity->phaseNodePath = aParentPath;
    activity->phaseNodePath.PushBack(aPhaseNodeID);

    activity->inputNode = inputNode;
    activity->inputSocket = {inputNode->socketName};
    activity->inputNodeKey = MakePhaseNodeKey(aParentPath, aPhaseNodeID, inputNode->id);

    s_activities[activity->name] = std::move(activity);

    return true;
}

bool App::QuestPhaseRegistry::RegisterCyberpsychoActivity(App::QuestPhaseGraphAccessor& aPhaseGraphAccessor,
                                                         Red::questPhaseInstance* aPhase,
                                                         const Red::Handle<Red::questGraphDefinition>& aPhaseGraph,
                                                         const Red::QuestNodePath& aParentPath, Red::NodeID aPhaseNodeID)
{
    auto poiMappin = aPhaseGraphAccessor.FindPointOfInterestMappin();

    if (!poiMappin)
        return false;

    auto activityName = ExtractMinorActivityName(poiMappin->path->realPath);

    if (!activityName)
        return false;

    auto characterKill = aPhaseGraphAccessor.FindCharacterKill();

    if (!characterKill)
        return false;

    // Check questSetVar_NodeType:glossary_cyberpsychosis

    return false;
}

Red::QuestNodeKey App::QuestPhaseRegistry::MakePhaseNodeKey(Red::QuestNodePath aParentPath, Red::NodeID aPhaseNodeID,
                                                           Red::NodeID aInputNodeID)
{
    if (aInputNodeID == static_cast<Red::NodeID>(-1))
    {
        return {aParentPath, aPhaseNodeID};
    }
    else
    {
        aParentPath.PushBack(aPhaseNodeID);
        return {aParentPath, aInputNodeID};
    }
}

Red::CName App::QuestPhaseRegistry::ExtractMinorActivityName(const Red::CString& aJournalPath)
{
    constexpr auto AddonPrefix = "ep1/";
    constexpr auto AddonPrefixLength = std::char_traits<char>::length(AddonPrefix);
    constexpr auto PointOfInterestPrefix = "points_of_interest/";
    constexpr auto PointOfInterestPrefixLength = std::char_traits<char>::length(PointOfInterestPrefix);
    constexpr auto MinorActivityPrefix = "minor_activities/";
    constexpr auto MinorActivityPrefixLength = std::char_traits<char>::length(MinorActivityPrefix);
    // constexpr auto MinorQuestPrefix = "minor_quests/";
    // constexpr auto MinorQuestPrefixLength = std::char_traits<char>::length(MinorQuestPrefix);

    std::string_view path(aJournalPath.c_str());

    if (path.starts_with(AddonPrefix))
    {
        path.remove_prefix(AddonPrefixLength);
    }

    if (path.starts_with(PointOfInterestPrefix))
    {
        path.remove_prefix(PointOfInterestPrefixLength);

        if (path.starts_with(MinorActivityPrefix))
        {
            path.remove_prefix(MinorActivityPrefixLength);
            return Red::CNamePool::Add(path.data());
        }

        // if (path.starts_with(MinorQuestPrefix))
        // {
        //     path.remove_prefix(MinorQuestPrefixLength);
        //     return Red::CNamePool::Add(path.data());
        // }
    }

    return {};
}

bool App::QuestPhaseRegistry::IsMinorActivityRelatedFact(const Red::CString& aFactName)
{
    constexpr auto MinorActivityPrefix = "ma_";
    constexpr auto TokenSuffix = "_token";
    constexpr auto TutorialSuffix = "_tutorial";

    std::string_view name(aFactName.c_str());

    if (name.ends_with(TutorialSuffix) || name.ends_with(TokenSuffix))
        return false;

    return true;

    // if (name.starts_with(MinorActivityPrefix))
    //     return true;
    //
    // if (name.find("_com_") != std::string_view::npos)
    //     return true;
    //
    // return false;
}

bool App::QuestPhaseRegistry::IsCombatActivityVariant(Red::gamedataMappinVariant aVariant)
{
    return aVariant == Red::gamedataMappinVariant::GangWatchVariant
        || aVariant == Red::gamedataMappinVariant::OutpostVariant;
}

bool App::QuestPhaseRegistry::HasRegisteredPhases()
{
    return !s_phaseInstances.empty();
}

Red::questPhaseInstance* App::QuestPhaseRegistry::GetPhaseInstance(Red::QuestNodeKey aPhasePath)
{
    const auto& it = s_phaseInstances.find(aPhasePath);

    if (it == s_phaseInstances.end())
        return nullptr;

    if (!it.value())
        return nullptr;

    return it.value().instance;
}

bool App::QuestPhaseRegistry::HasRegisteredActivities()
{
    return !s_activities.empty();
}

Core::Vector<Core::SharedPtr<App::ActivityDefinition>> App::QuestPhaseRegistry::GetAllActivities()
{
    Core::Vector<Core::SharedPtr<App::ActivityDefinition>> activities;

    for (const auto& [_, activity] : s_activities)
    {
        activities.push_back(activity);
    }

    return activities;
}

Core::Vector<Red::CName> App::QuestPhaseRegistry::GetAllActivityNames()
{
    Core::Vector<Red::CName> activities;

    for (const auto& [name, _] : s_activities)
    {
        activities.push_back(name);
    }

    return activities;
}

Core::SharedPtr<App::ActivityDefinition> App::QuestPhaseRegistry::FindActivity(Red::CName aName)
{
    const auto& it = s_activities.find(aName);

    if (it == s_activities.end())
        return {};

    return it.value();
}

void App::QuestPhaseRegistry::DumpActivities()
{
#ifndef NDEBUG
    LogDebug("| Type | Activity | Area | District | Description |");
    LogDebug("|:---|:---|:---|:---|:---|");

    for (const auto& [_, activity] : s_activities)
    {
        Red::CString localizedTitle;
        Red::CallGlobal("GetLocalizedTextByKey", localizedTitle, activity->title);

        Red::CString localizedDescription;
        Red::CallGlobal("GetLocalizedTextByKey", localizedDescription, activity->description);

        Red::CName areaName;
        Red::CallGlobal("EnumValueToName", areaName, Red::GetTypeName<Red::gamedataDistrict>(), activity->area);

        Red::CName districtName;
        Red::CallGlobal("EnumValueToName", districtName, Red::GetTypeName<Red::gamedataDistrict>(), activity->district);

        LogDebug("| `{}` | `{}` | `{}` | `{}` | {}: {} |",
                 activity->kind.ToString(),
                 activity->name.ToString(),
                 areaName.ToString(),
                 districtName.ToString(),
                 localizedTitle.c_str(),
                 localizedDescription.c_str());
    }
#endif
}
