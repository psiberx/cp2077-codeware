#include "OpenWorldRegistry.hpp"
#include "App/Quest/QuestPhaseGraphBuilder.hpp"
#include "App/World/DistrictResolver.hpp"
#include "Red/TweakDB.hpp"

namespace
{
constexpr auto MinorActivitiesResource = R"(base\open_world\minor_activities\open_world_minor_activities.questphase)";
}

void App::OpenWorldRegistry::OnBootstrap()
{
    HookAfter<Raw::QuestLoader::PhasePreloadCheck>(&OpenWorldRegistry::OnPhasePreloadCheck);
    HookAfter<Raw::QuestPhaseInstance::Initialize>(&OpenWorldRegistry::OnInitializePhase);
}

void App::OpenWorldRegistry::OnPhasePreloadCheck(bool& aPreload, void* aLoader, const Red::QuestNodePath& aPhaseNodePath)
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

void App::OpenWorldRegistry::OnInitializePhase(Red::questPhaseInstance* aPhase, Red::QuestContext& aContext,
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
    RegisterCrimeActivity(phaseGraphAccessor, aPhase, aPhaseGraph, aParentPath, aPhaseNodeID);
    // RegisterCyberpsychoActivity(phaseGraphAccessor, aPhase, aPhaseGraph, aParentPath, aPhaseNodeID);
}

bool App::OpenWorldRegistry::RegisterCrimeActivity(App::QuestPhaseGraphAccessor& aPhaseGraphAccessor,
                                                   Red::questPhaseInstance* aPhase,
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
    auto spawners = aPhaseGraphAccessor.FindSpawners();

    if (communities.empty() && spawners.empty())
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
        activity->communityRefs.push_back(community->spawnerReference);
    }

    for (const auto& spawner : spawners)
    {
        activity->spawnerRefs.push_back(spawner->spawnerReference);
    }

    for (const auto& areaLink : aPhaseGraphAccessor.FindAreaLinks())
    {
        if (areaLink->PSClassName)
        {
            activity->persistenceRefs.push_back({areaLink->objectRef.reference, areaLink->componentName});
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
        activity->journalHashes.push_back(Red::Murmur3_32(journalObjective->path->realPath.c_str()));
    }

    for (const auto& factChange : aPhaseGraphAccessor.FindFactChanges())
    {
        if (IsMinorActivityRelatedFact(factChange->factName))
        {
            activity->namedFacts.emplace_back(factChange->factName.c_str());
        }
    }

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
            for (const auto& suffix : {"_shard", "_onscreen", "_onscreen_01"})
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

            auto pauseNode = phaseGraphBuilder.AddStaticEntitySpawnWait(activity->lootContainerRef);
            auto eventNode = phaseGraphBuilder.AddEventDispatch(activity->lootContainerRef);
            eventNode->event = Red::MakeHandle<Red::gameResetContainerEvent>();

            phaseGraphBuilder.AddConnection(inputNode, pauseNode);
            phaseGraphBuilder.AddConnection(pauseNode, eventNode);
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
            resetNode->id = prefabNode->id;
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
            resetNode->id = prefabNode->id;
            resetNode->type = resetNodeType;

            activity->resetNodes.push_back(std::move(resetNode));
        }
    }

    activity->phaseInstance = aPhase;
    activity->phaseGraph = aPhaseGraph;
    activity->phaseNodeKey = MakePhaseNodeKey(aParentPath, aPhaseNodeID);
    activity->phaseNodePath = aParentPath;
    activity->phaseNodePath.PushBack(aPhaseNodeID);

    activity->inputNode = inputNode;
    activity->inputSocket = {inputNode->socketName};
    activity->inputNodeKey = MakePhaseNodeKey(aParentPath, aPhaseNodeID, inputNode->id);

    s_activities[activity->name] = std::move(activity);

    return true;
}

bool App::OpenWorldRegistry::RegisterCyberpsychoActivity(App::QuestPhaseGraphAccessor& aPhaseGraphAccessor,
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

Red::QuestNodeKey App::OpenWorldRegistry::MakePhaseNodeKey(Red::QuestNodePath aParentPath, Red::NodeID aPhaseNodeID,
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

Red::CName App::OpenWorldRegistry::ExtractMinorActivityName(const Red::CString& aJournalPath)
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

bool App::OpenWorldRegistry::IsMinorActivityRelatedFact(const Red::CString& aFactName)
{
    constexpr auto MinorActivityPrefix = "ma_";
    constexpr auto TokenSuffix = "_token";
    constexpr auto TutorialSuffix = "_tutorial";

    std::string_view name(aFactName.c_str());
    return name.starts_with(MinorActivityPrefix) && !name.ends_with(TokenSuffix) && !name.ends_with(TutorialSuffix);
}

bool App::OpenWorldRegistry::IsCombatActivityVariant(Red::gamedataMappinVariant aVariant)
{
    return aVariant == Red::gamedataMappinVariant::GangWatchVariant
        || aVariant == Red::gamedataMappinVariant::OutpostVariant;
}

Core::Vector<Core::SharedPtr<App::ActivityDefinition>> App::OpenWorldRegistry::GetAllActivities()
{
    Core::Vector<Core::SharedPtr<App::ActivityDefinition>> activities;

    for (const auto& [_, activity] : s_activities)
    {
        activities.push_back(activity);
    }

    return activities;
}

Core::Vector<Red::CName> App::OpenWorldRegistry::GetAllActivityNames()
{
    Core::Vector<Red::CName> activities;

    for (const auto& [name, _] : s_activities)
    {
        activities.push_back(name);
    }

    return activities;
}

Core::SharedPtr<App::ActivityDefinition> App::OpenWorldRegistry::FindActivity(Red::CName aName)
{
    const auto& it = s_activities.find(aName);

    if (it == s_activities.end())
        return {};

    return it.value();
}

Red::WeakHandle<Red::questPhaseInstance> App::OpenWorldRegistry::GetPhaseInstance(Red::QuestNodeKey aPhasePath)
{
    const auto& it = s_phaseInstances.find(aPhasePath);

    if (it == s_phaseInstances.end())
        return {};

    return it.value();
}

void App::OpenWorldRegistry::DumpActivities()
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
