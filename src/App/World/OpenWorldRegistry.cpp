#include "OpenWorldRegistry.hpp"
#include "App/World/DistrictResolver.hpp"
#include "Red/TweakDB.hpp"

void App::OpenWorldRegistry::OnBootstrap()
{
    HookAfter<Raw::QuestPhaseInstance::Initialize>(&OpenWorldRegistry::OnInitializePhase);
}

void App::OpenWorldRegistry::OnInitializePhase(Red::questPhaseInstance* aPhase, Red::QuestContext& aContext,
                                               const Red::Handle<Red::questQuestPhaseResource>& aPhaseResource,
                                               const Red::Handle<Red::questGraphDefinition>& aPhaseGraph,
                                               const Red::NodePath& aParentPath, Red::NodeID aPhaseNodeID)
{
    if (aParentPath.size == 0 && aPhaseNodeID == 0)
    {
        m_activities.clear();
    }

    if (!aPhaseResource)
        return;

    QuestPhaseGraphAccessor phaseGraphAccessor(aPhaseGraph);

    RegisterCrimeActivity(phaseGraphAccessor, aPhase, aPhaseGraph, aParentPath, aPhaseNodeID);
    // RegisterCyberpsychoActivity(phaseGraphAccessor, aPhase, aPhaseGraph, aParentPath, aPhaseNodeID);
}

bool App::OpenWorldRegistry::RegisterCrimeActivity(App::QuestPhaseGraphAccessor& aPhaseGraphAccessor,
                                                   Red::questPhaseInstance* aPhase,
                                                   const Red::Handle<Red::questGraphDefinition>& aPhaseGraph,
                                                   const Red::NodePath& aParentPath, Red::NodeID aPhaseNodeID)
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
    }

    {
        bool success;
        bool active;
        uint16_t phaseInt;
        uint16_t variantInt;

        auto mappinSystem = Red::GetGameSystem<Red::gamemappinsIMappinSystem>();
        Red::CallVirtual(mappinSystem, "GetPointOfInterestMappinSavedState", success,
                         activity->mappinHash, phaseInt, variantInt, active);

        if (!success)
            return false;

        auto variant = static_cast<Red::gamedataMappinVariant>(variantInt);
        Red::CallGlobal("gameuiMappinUIUtils::MappinToString;gamedataMappinVariant", activity->title, variant);
        Red::CallGlobal("gameuiMappinUIUtils::MappinToDescriptionString;gamedataMappinVariant", activity->description, variant);
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
            activity->factHashes.emplace_back(factChange->factName.c_str());
        }
    }

    for (const auto& lootObjective : aPhaseGraphAccessor.FindLootObjectives())
    {
        activity->lootItemIDs.push_back(lootObjective->itemID);
    }

    if (auto lootContainer = aPhaseGraphAccessor.FindLootContainer())
    {
        activity->lootContainerRef = lootContainer->objectRef;

        activity->persistenceRefs.push_back({lootContainer->objectRef});
        activity->persistenceRefs.push_back({lootContainer->objectRef, "inventory"});
        activity->persistenceRefs.push_back({lootContainer->objectRef, "interactions"});

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
    }

    for (const auto& prefabNode : aPhaseGraphAccessor.GetNodesOfType<Red::questWorldDataManagerNodeDefinition>())
    {
        if (auto& prefabNodeType = Red::Cast<Red::questTogglePrefabVariant_NodeType>(prefabNode->type))
        {
            auto patchNode = Red::MakeHandle<Red::questWorldDataManagerNodeDefinition>();
            patchNode->id = prefabNode->id;

            auto patchNodeType = Red::MakeHandle<Red::questTogglePrefabVariant_NodeType>();
            patchNodeType->params = prefabNodeType->params;
            for (auto& param : patchNodeType->params)
            {
                for (auto& state : param.variantStates)
                {
                    state.show = !state.show;
                }
            }

            patchNode->type = patchNodeType;
            activity->resetNodes.push_back(std::move(patchNode));
        }

        if (auto& prefabNodeType = Red::Cast<Red::questShowWorldNode_NodeType>(prefabNode->type))
        {
            auto patchNode = Red::MakeHandle<Red::questWorldDataManagerNodeDefinition>();
            patchNode->id = prefabNode->id;

            auto patchNodeType = Red::MakeHandle<Red::questShowWorldNode_NodeType>();
            patchNodeType->objectRef = prefabNodeType->objectRef;
            patchNodeType->componentName = prefabNodeType->componentName;
            patchNodeType->isPlayer = prefabNodeType->isPlayer;
            patchNodeType->show = !prefabNodeType->show;

            patchNode->type = patchNodeType;
            activity->resetNodes.push_back(std::move(patchNode));
        }
    }

    activity->phaseInstance = aPhase;
    activity->phaseGraph = aPhaseGraph;

    activity->inputNode = inputNode;
    activity->inputSocket = {inputNode->socketName};
    activity->inputNodePath = MakePhaseNodePath(aParentPath, aPhaseNodeID, inputNode->id);

    m_activities[activity->name] = std::move(activity);

#ifndef NDEBUG
    LogDebug("Minor Activity Discovered: {}", activityName.ToString());
#endif

    return true;
}

bool App::OpenWorldRegistry::RegisterCyberpsychoActivity(App::QuestPhaseGraphAccessor& aPhaseGraphAccessor,
                                                         Red::questPhaseInstance* aPhase,
                                                         const Red::Handle<Red::questGraphDefinition>& aPhaseGraph,
                                                         const Red::NodePath& aParentPath, Red::NodeID aPhaseNodeID)
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

Red::PhaseNodePath App::OpenWorldRegistry::MakePhaseNodePath(Red::NodePath aParentPath, Red::NodeID aPhaseNodeID,
                                                             Red::NodeID aInputNodeID)
{
    aParentPath.PushBack(aPhaseNodeID);
    return {aParentPath, aInputNodeID};
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

Core::Vector<Core::SharedPtr<App::ActivityDefinition>> App::OpenWorldRegistry::GetAllActivities()
{
    Core::Vector<Core::SharedPtr<App::ActivityDefinition>> activities;

    for (const auto& [_, activity] : m_activities)
    {
        activities.push_back(activity);
    }

    return activities;
}

Core::Vector<Red::CName> App::OpenWorldRegistry::GetAllActivityNames()
{
    Core::Vector<Red::CName> activities;

    for (const auto& [name, _] : m_activities)
    {
        activities.push_back(name);
    }

    return activities;
}

Core::SharedPtr<App::ActivityDefinition> App::OpenWorldRegistry::FindActivity(Red::CName aName)
{
    const auto& it = m_activities.find(aName);

    if (it == m_activities.end())
        return {};

    return it.value();
}
