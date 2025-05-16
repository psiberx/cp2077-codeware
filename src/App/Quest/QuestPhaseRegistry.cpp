#include "QuestPhaseRegistry.hpp"
#include "App/Device/ResetSecuritySystemNetwork.hpp"
#include "App/Quest/QuestPhaseGraphBuilder.hpp"
#include "App/World/DistrictResolver.hpp"
#include "Red/NodeRef.hpp"
#include "Red/TweakDB.hpp"

namespace
{
constexpr auto MinorActivitiesResource = Red::ResourcePath(R"(base\open_world\minor_activities\open_world_minor_activities.questphase)");

constexpr auto OpenWorldPhaseResources = {
    MinorActivitiesResource,
    Red::ResourcePath(R"(base\open_world\city_scenes\open_world_city_scenes.questphase)"),
    Red::ResourcePath(R"(base\open_world\community\global_phase\open_world_global_commuinity_phase.questphase)"),
    Red::ResourcePath(R"(base\open_world\fixers\open_world_fixers.questphase)"),
    Red::ResourcePath(R"(base\open_world\phases\city_entities\city_entities.questphase)"),
    Red::ResourcePath(R"(base\open_world\vendors\open_world_vendors.questphase)"),
    Red::ResourcePath(R"(base\quest\bugfixing\open_world_bugfixing.questphase)"),
};
}

void App::QuestPhaseRegistry::OnBootstrap()
{
    // HookAfter<Raw::QuestLoader::PhasePreloadCheck>(&QuestPhaseRegistry::OnPhasePreloadCheck);
    // HookAfter<Raw::QuestPhaseInstance::Initialize>(&QuestPhaseRegistry::OnInitializePhase);
}

void App::QuestPhaseRegistry::OnPhasePreloadCheck(bool& aPreload, void* aLoader,
                                                  const Red::QuestNodePath& aPhaseNodePath)
{
    if (!aPreload)
    {
        for (const auto& openWorldPhasePath : OpenWorldPhaseResources)
        {
            auto openWorldPhaseNodePathIt = s_openWorldPhaseNodePaths.find(openWorldPhasePath);
            if (openWorldPhaseNodePathIt == s_openWorldPhaseNodePaths.end())
            {
                auto* phaseNodePath = Raw::QuestLoader::NodePathMap::Ref(aLoader).Get(openWorldPhasePath);

                if (!phaseNodePath)
                    continue;

                openWorldPhaseNodePathIt = s_openWorldPhaseNodePaths.insert({openWorldPhasePath, *phaseNodePath}).first;
            }

            if (Red::IsRelatedQuestNodePath(openWorldPhaseNodePathIt.value(), aPhaseNodePath))
            {
                auto& preloadList = Raw::QuestLoader::PreloadList::Ref(aLoader);
                preloadList->PushBack(aPhaseNodePath);

                aPreload = true;
                break;
            }
        }
    }
}

void App::QuestPhaseRegistry::OnInitializePhase(Red::questPhaseInstance* aPhase, Red::QuestContext& aContext,
                                                const Red::Handle<Red::questQuestPhaseResource>& aPhaseResource,
                                                Red::Handle<Red::questGraphDefinition>& aPhaseGraph,
                                                const Red::QuestNodePath& aParentNodePath,
                                                Red::QuestNodeID aPhaseNodeID)
{
    std::unique_lock phasesLockRW(s_phasesLock);

    if (aParentNodePath.size == 0 && aPhaseNodeID == 0)
    {
        std::unique_lock activitiesLockRW(s_activitiesLock);

        s_activitiesReady = false;
        s_activities.clear();

        s_phasesReady = false;
        s_phases.clear();
    }

    auto& phaseNodePathHash = Raw::QuestPhaseInstance::NodePathHash::Ref(aPhase);
    s_phases[phaseNodePathHash] = Red::AsWeakHandle(aPhase);

    if (aPhaseResource)
    {
        auto& phaseNodePath = Raw::QuestPhaseInstance::NodePath::Ref(aPhase);

        for (const auto& openWorldPhasePath : OpenWorldPhaseResources)
        {
            if (aPhaseResource->path == openWorldPhasePath)
            {
                s_openWorldPhaseNodePaths[openWorldPhasePath] = phaseNodePath;
                break;
            }
        }
    }
}

bool App::QuestPhaseRegistry::PhasesInitialized()
{
    std::shared_lock phasesLockR(s_phasesLock);

    return !s_phases.empty();
}

Red::questPhaseInstance* App::QuestPhaseRegistry::GetPhaseInstance(Red::QuestNodePathHash aPhasePathHash)
{
    std::shared_lock phasesLockR(s_phasesLock);
    const auto& it = s_phases.find(aPhasePathHash);

    if (it == s_phases.end())
        return nullptr;

    if (!it.value())
        return nullptr;

    return it.value().instance;
}

bool App::QuestPhaseRegistry::ActivitiesInitialized()
{
    std::shared_lock activitiesLockR(s_activitiesLock);

    return s_activitiesReady;
}

void App::QuestPhaseRegistry::InitializeActivities()
{
    if (ActivitiesInitialized())
        return;

    std::shared_lock phasesLockR(s_phasesLock);
    std::unique_lock activitiesLockRW(s_activitiesLock);

    Core::Vector<Red::questPhaseInstance*> communityPhases;

    for (auto& [_, phaseWeak] : s_phases)
    {
        auto phase = phaseWeak.Lock();

        if (!phase)
            continue;

        auto& phaseInstance = phase.instance;
        auto& phaseResource = Raw::QuestPhaseInstance::Resource::Ref(phaseInstance);

        if (!phaseResource)
            continue;

        auto& phaseGraph = Raw::QuestPhaseInstance::Graph::Ref(phaseInstance);
        auto& phaseNodePath = Raw::QuestPhaseInstance::NodePath::Ref(phaseInstance);
        auto& phaseNodePathHash = Raw::QuestPhaseInstance::NodePathHash::Ref(phaseInstance);

        for (const auto& openWorldPhasePath : OpenWorldPhaseResources)
        {
            const auto& openWorldPhaseNodePathIt = s_openWorldPhaseNodePaths.find(openWorldPhasePath);
            if (openWorldPhaseNodePathIt == s_openWorldPhaseNodePaths.end())
                continue;

            const auto& openWorldPhaseNodePath = openWorldPhaseNodePathIt.value();
            if (!Red::IsRelatedQuestNodePath(openWorldPhaseNodePath, phaseNodePath))
                continue;

            if (openWorldPhasePath == MinorActivitiesResource)
            {
                QuestPhaseGraphAccessor phaseGraphAccessor{phaseGraph, true};
                ApplyActivityBugfixes(phaseGraphAccessor, phaseResource, phaseGraph);
                RegisterMinorActivity(phaseGraphAccessor, phaseInstance, phaseResource, phaseGraph, phaseNodePath);
            }
            else
            {
                communityPhases.push_back(phaseInstance);
            }

            break;
        }
    }

#ifndef NDEBUG
    for (auto& phaseInstance : communityPhases)
    {
        auto& phaseGraph = Raw::QuestPhaseInstance::Graph::Ref(phaseInstance);
        auto& phaseNodePathHash = Raw::QuestPhaseInstance::NodePathHash::Ref(phaseInstance);

        QuestPhaseGraphAccessor phaseGraphAccessor{phaseGraph, true};

        for (const auto& factCondition : phaseGraphAccessor.FindFactConditions())
        {
            Red::FactID factID{factCondition->factName.c_str()};

            auto it = s_activitiesByFacts.find(factID);
            if (it != s_activitiesByFacts.end())
            {
                s_populationsByFacts[factID].push_back(phaseNodePathHash);

                for (const auto& activityName : it.value())
                {
                    LogDebug("Population: {} {} {}", activityName.ToString(), phaseNodePathHash, factCondition->factName.c_str());
                }
            }
        }
    }
#endif

    s_activitiesReady = true;
}

bool App::QuestPhaseRegistry::ApplyActivityBugfixes(App::QuestPhaseGraphAccessor& aPhaseGraphAccessor,
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

        return true;
    }

    return false;
}

bool App::QuestPhaseRegistry::RegisterMinorActivity(App::QuestPhaseGraphAccessor& aPhaseGraphAccessor,
                                                    Red::questPhaseInstance* aPhase,
                                                    const Red::Handle<Red::questQuestPhaseResource>& aPhaseResource,
                                                    Red::Handle<Red::questGraphDefinition>& aPhaseGraph,
                                                    const Red::QuestNodePath& aPhaseNodePath)
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

    for (const auto& journalObjective : aPhaseGraphAccessor.FindJournalConditions())
    {
        activity->journalHashes.push_back(Red::Murmur3_32(journalObjective->realPath.c_str()));
    }

    for (const auto& factChange : aPhaseGraphAccessor.FindFactChanges())
    {
        if (IsMinorActivityRelatedFact(factChange->factName))
        {
            activity->namedFacts.emplace_back(factChange->factName.c_str());
        }
    }

    for (const auto& graphNodePath : aPhaseGraphAccessor.GetAllGraphNodePaths(aPhaseNodePath))
    {
        activity->graphFacts.emplace_back(graphNodePath);
    }

    for (const auto& lootObjective : aPhaseGraphAccessor.FindLootConditions())
    {
        activity->lootItemIDs.push_back(lootObjective->itemID);
    }

    if (auto lootContainer = aPhaseGraphAccessor.FindLootContainerCondition())
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
    }

    for (const auto& suffix : {"_dvc_sec_sys", "_dvc_sec_system", "_dvc_security_system"})
    {
        Red::NodeRef securitySystemRef{Red::FNV1a64(suffix, activityName)};

        if (Red::ResolveNodeRef(securitySystemRef))
        {
            activity->securitySystemRef = securitySystemRef;

            activity->persistenceRefs.push_back({securitySystemRef});
            activity->persistenceRefs.push_back({securitySystemRef, "controller"});
            activity->persistenceRefs.push_back({securitySystemRef, "master"});

#ifndef NDEBUG
            LogDebug("SecuritySystem: {}{}", activityName.ToString(), suffix);
#endif
            break;
        }
    }

    {
        QuestPhaseGraphBuilder phaseGraphBuilder{aPhaseGraph};

        if (activity->lootContainerRef)
        {
            auto pauseNode = phaseGraphBuilder.AddStaticEntitySpawnWait(activity->lootContainerRef);
            auto eventNode = phaseGraphBuilder.AddEventDispatch(activity->lootContainerRef);
            eventNode->event = Red::MakeHandle<Red::gameResetContainerEvent>();

            phaseGraphBuilder.AddConnection(inputNode, pauseNode);
            phaseGraphBuilder.AddConnection(pauseNode, eventNode);
        }

        if (activity->securitySystemRef)
        {
            auto eventNode = phaseGraphBuilder.AddEventDispatch(activity->securitySystemRef);
            eventNode->event = Red::MakeHandle<ResetSecuritySystemNetwork>();
            eventNode->PSClassName = "SecuritySystemControllerPS";
            eventNode->componentName = "controller";

            phaseGraphBuilder.AddConnection(inputNode, eventNode);
        }
    }

    GenerateResetNodes(aPhaseGraphAccessor, aPhaseResource, activity->resetNodes);

    activity->phaseInstance = aPhase;
    activity->phaseGraph = aPhaseGraph;
    activity->phaseResource = aPhaseResource;
    activity->phaseNodeKey = aPhaseNodePath;
    activity->phaseNodePath = aPhaseNodePath;

    activity->inputNode = inputNode;
    activity->inputSocket = {inputNode->socketName};
    activity->inputNodeKey = {aPhaseNodePath, inputNode->id};

    for (const auto& factID : activity->namedFacts)
    {
        s_activitiesByFacts[factID].push_back(activity->name);
    }

    s_activities[activity->name] = std::move(activity);

    return true;
}

bool App::QuestPhaseRegistry::RegisterCyberpsychoActivity(App::QuestPhaseGraphAccessor& aPhaseGraphAccessor,
                                                          Red::questPhaseInstance* aPhase,
                                                          const Red::Handle<Red::questGraphDefinition>& aPhaseGraph,
                                                          const Red::QuestNodePath& aParentPath, Red::QuestNodeID aPhaseNodeID)
{
    auto poiMappin = aPhaseGraphAccessor.FindPointOfInterestMappin();

    if (!poiMappin)
        return false;

    auto activityName = ExtractMinorActivityName(poiMappin->path->realPath);

    if (!activityName)
        return false;

    auto characterKill = aPhaseGraphAccessor.FindCharacterKillCondition();

    if (!characterKill)
        return false;

    // Check questSetVar_NodeType:glossary_cyberpsychosis

    return false;
}

void App::QuestPhaseRegistry::GenerateResetNodes(App::QuestPhaseGraphAccessor& aPhaseGraphAccessor,
                                                 const Red::Handle<Red::questQuestPhaseResource>& aPhaseResource,
                                                 Core::Vector<Red::Handle<Red::questNodeDefinition>>& aResetNodes)
{
    Red::QuestNodeID resetNodeID = 900;

    for (const auto& factChange : aPhaseGraphAccessor.FindFactChanges())
    {
        if (IsMinorActivityRelatedFact(factChange->factName))
        {
            auto resetNodeType = Red::MakeHandle<Red::questSetVar_NodeType>();
            resetNodeType->factName = factChange->factName;
            resetNodeType->setExactValue = true;
            resetNodeType->value = 0;

            auto resetNode = Red::MakeHandle<Red::questFactsDBManagerNodeDefinition>();
            resetNode->id = ++resetNodeID;
            resetNode->type = resetNodeType;

            aResetNodes.push_back(std::move(resetNode));
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

            aResetNodes.push_back(std::move(resetNode));
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

            aResetNodes.push_back(std::move(resetNode));
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

            aResetNodes.push_back(std::move(resetNode));
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
                resetNode->id = ++resetNodeID;
                resetNode->event = Red::Handle(reinterpret_cast<Red::IScriptable*>(resetEvent));
                resetNode->objectRef = managerNode->objectRef;
                resetNode->managerName = managerNode->managerName;
                resetNode->componentName = managerNode->componentName;
                resetNode->PSClassName = managerNode->PSClassName;
                resetNode->isObjectPlayer = managerNode->isObjectPlayer;
                resetNode->isUiEvent = managerNode->isUiEvent;

                aResetNodes.push_back(std::move(resetNode));
            }
        }
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
    constexpr auto AchievementSuffix = "_achievement";

    std::string_view name(aFactName.c_str());

    if (name.ends_with(TutorialSuffix) || name.ends_with(TokenSuffix) || name.ends_with(AchievementSuffix))
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

Core::Vector<Core::SharedPtr<App::ActivityDefinition>> App::QuestPhaseRegistry::GetAllActivities()
{
    std::shared_lock activitiesLockR(s_activitiesLock);
    Core::Vector<Core::SharedPtr<App::ActivityDefinition>> activities;

    for (const auto& [_, activity] : s_activities)
    {
        activities.push_back(activity);
    }

    return activities;
}

Core::Vector<Red::CName> App::QuestPhaseRegistry::GetAllActivityNames()
{
    std::shared_lock activitiesLockR(s_activitiesLock);
    Core::Vector<Red::CName> activities;

    for (const auto& [name, _] : s_activities)
    {
        activities.push_back(name);
    }

    return activities;
}

Core::SharedPtr<App::ActivityDefinition> App::QuestPhaseRegistry::FindActivity(Red::CName aName)
{
    std::shared_lock activitiesLockR(s_activitiesLock);
    const auto& it = s_activities.find(aName);

    if (it == s_activities.end())
        return {};

    return it.value();
}

void App::QuestPhaseRegistry::DumpActivities()
{
#ifndef NDEBUG
    std::shared_lock activitiesLockR(s_activitiesLock);

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
