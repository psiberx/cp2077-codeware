#include "OpenWorldSystem.hpp"
#include "Core/Facades/Container.hpp"
#include "Core/Facades/Log.hpp"
#include "Red/CommunitySystem.hpp"
#include "Red/JournalManager.hpp"
#include "Red/MappinSystem.hpp"
#include "Red/TweakDB.hpp"

void App::OpenWorldSystem::OnWorldAttached(Red::world::RuntimeScene*)
{
    m_registry = Core::Resolve<OpenWorldRegistry>();

    m_communitySystem = Red::GetGameSystem<Red::gameICommunitySystem>();
    m_populationSystem = Red::GetGameSystem<Red::gameIPopulationSystem>();
    m_persistencySystem = Red::GetGameSystem<Red::gameIPersistencySystem>();
    m_containerManager = Red::GetGameSystem<Red::gameIContainerManager>();
    m_journalManager = Red::GetGameSystem<Red::gameIJournalManager>();
    m_mappinSystem = Red::GetGameSystem<Red::gamemappinsIMappinSystem>();
    m_questsSystem = Red::GetGameSystem<Red::questIQuestsSystem>();
    m_factManager = Raw::QuestsSystem::FactManager::Ptr(m_questsSystem);

    m_ready = true;
}

void App::OpenWorldSystem::OnAfterWorldDetach()
{
    m_ready = false;
}

App::OpenWorldActivityState App::OpenWorldSystem::GetActivity(Red::CName aName)
{
    const auto& activity = m_registry->FindActivity(aName);

    if (!activity)
        return {};

    return MakeActivityState(activity);
}

Red::DynArray<App::OpenWorldActivityState> App::OpenWorldSystem::GetActivities()
{
    Red::DynArray<OpenWorldActivityState> states;

    for (const auto& activity : m_registry->GetAllActivities())
    {
        states.EmplaceBack(MakeActivityState(activity));
    }

    return states;
}

App::OpenWorldActivityResult App::OpenWorldSystem::StartActivity(Red::CName aName, Red::Optional<bool> aForce)
{
    const auto& activity = m_registry->FindActivity(aName);

    if (!activity)
        return OpenWorldActivityResult::NotFound;

    auto state = MakeActivityState(activity);

    if (!state.completed)
    {
        if (state.discovered)
            return OpenWorldActivityResult::Unfinished;

        if (!aForce)
            return OpenWorldActivityResult::Undiscovered;
    }

    return ProcessActivity(activity);
}

int32_t App::OpenWorldSystem::StartActivities(Red::Optional<OpenWorldActivityRequest>& aRequest)
{
    int32_t successful = 0;
    uint32_t gameTime = 0;
    float realTimeMultiplier = 1.0;

    if (aRequest->HasCooldown())
    {
        Red::ScriptGameInstance game;
        Red::CallStatic("ScriptGameInstance", "GetGameTime", gameTime, game);
        realTimeMultiplier = Red::GetFlatValue<float>("timeSystem.settings.realTimeMultiplier");
    }

    for (const auto& activity : m_registry->GetAllActivities())
    {
        auto state = MakeActivityState(activity);

        if (!state.completed)
        {
            if (state.discovered)
                continue;

            if (!aRequest->force)
                continue;
        }

        if (!aRequest->Match(state, gameTime, realTimeMultiplier))
            continue;

        if (ProcessActivity(activity) == OpenWorldActivityResult::OK)
        {
            ++successful;
        }
    }

    return successful;
}

App::OpenWorldActivityState App::OpenWorldSystem::MakeActivityState(
    const Core::SharedPtr<App::ActivityDefinition>& aActivity)
{
    OpenWorldActivityState state(aActivity);
    state.timestamp = Raw::JournalManager::GetEntryTimestamp(m_journalManager, aActivity->mappinEntry);

    auto phase = Raw::MappinSystem::GetPoiMappinPhase(m_mappinSystem, aActivity->mappinHash);
    state.completed = (phase == Red::gamedataMappinPhase::CompletedPhase);
    state.discovered = state.completed || (phase == Red::gamedataMappinPhase::DiscoveredPhase);

    return state;
}

bool App::OpenWorldSystem::IsActivityCompleted(const Core::SharedPtr<App::ActivityDefinition>& aActivity)
{
    auto phase = Raw::MappinSystem::GetPoiMappinPhase(m_mappinSystem, aActivity->mappinHash);
    if (phase != Red::gamedataMappinPhase::Invalid)
    {
        return phase == Red::gamedataMappinPhase::CompletedPhase;
    }

    // Red::Handle<Red::gameJournalEntry> entry;
    // Raw::JournalManager::GetEntryByHash(m_journalManager, entry, aActivity->mappinHash);
    // if (entry)
    // {
    //     auto state = Raw::JournalManager::GetEntryState(m_journalManager, entry);
    //     if (state != Red::gameJournalEntryState::Undefined)
    //     {
    //         return state == Red::gameJournalEntryState::Inactive || state == Red::gameJournalEntryState::Succeeded;
    //     }
    // }

    return false;
}

App::OpenWorldActivityResult App::OpenWorldSystem::ProcessActivity(
    const Core::SharedPtr<App::ActivityDefinition>& aActivity)
{
    Core::Vector<Red::EntityID> communityIDs;
    Core::Vector<Red::EntityID> spawnerIDs;
    Red::DynArray<Red::EntityID> entityIDs;

    for (const auto& communityRef : aActivity->communityRefs)
    {
        auto communityID = ResolveNodeRef(communityRef);

        if (!communityID)
            continue;

        Red::WeakPtr<Red::Community> community;
        Raw::CommunitySystem::GetCommunity(m_communitySystem, community, communityID);

        if (!community.instance)
            continue;

        communityIDs.push_back(communityID);

        Red::DynArray<Red::EntityID> communityEntityIDs;
        community.instance->GetActiveEntityIDs(communityEntityIDs);
        for (const auto& entityID : communityEntityIDs)
        {
            entityIDs.PushBack(entityID);
        }

        for (auto& entry : community.instance->entries)
        {
            entry->unk2C = -1;

            for (const auto& entityID : entry->spawner->restoredEntityIDs)
            {
                entityIDs.PushBack(entityID);
            }
            for (const auto& entityID : entry->spawner->spawnedEntityIDs)
            {
                entityIDs.PushBack(entityID);
            }
            for (const auto& entityID : entry->spawner->spawningStubIds)
            {
                entityIDs.PushBack(entityID);
            }
            for (const auto& entityID : entry->spawner->reservedEntityIDs)
            {
                entityIDs.PushBack(entityID);
            }
        }
    }

    for (const auto& spawnerRef : aActivity->spawnerRefs)
    {
        auto spawnerID = ResolveNodeRef(spawnerRef);

        if (!spawnerID)
            continue;

        Red::WeakPtr<Red::Spawner> spawner;
        Raw::CommunitySystem::GetSpawner(m_communitySystem, spawner, spawnerID);

        if (!spawner.instance)
            continue;

        spawnerIDs.push_back(spawnerID);

        Red::DynArray<Red::EntityID> spawnerEntityIDs;
        spawner.instance->GetActiveEntityIDs(spawnerEntityIDs);
        for (const auto& entityID : spawnerEntityIDs)
        {
            entityIDs.PushBack(entityID);
        }

        for (const auto& entityID : spawner.instance->restoredEntityIDs)
        {
            entityIDs.PushBack(entityID);
        }
        for (const auto& entityID : spawner.instance->spawnedEntityIDs)
        {
            entityIDs.PushBack(entityID);
        }
        for (const auto& entityID : spawner.instance->reservedEntityIDs)
        {
            entityIDs.PushBack(entityID);
        }
    }

    for (const auto& entityID : entityIDs)
    {
        Red::Handle<Red::Entity> entity;
        m_populationSystem->FindEntity(entity, entityID);

        if (entity)
            return OpenWorldActivityResult::StillSpawned;
    }

    for (const auto& persistenceRef : aActivity->persistenceRefs)
    {
        auto objectID = ResolveNodeRef(persistenceRef.objectRef);

        if (!objectID)
            continue;

        Red::Handle<Red::Entity> entity;
        Red::ScriptGameInstance game;
        Red::CallStatic("ScriptGameInstance", "FindEntityByID", entity, game, objectID);

        if (entity)
            return OpenWorldActivityResult::StillSpawned;
    }

    for (const auto& communityID : communityIDs)
    {
        Raw::CommunitySystem::DeactivateCommunity(m_communitySystem, communityID, {});
        Raw::CommunitySystem::Update(m_communitySystem, true);

        Raw::CommunitySystem::ResetCommunity(m_communitySystem, communityID, {});
        Raw::CommunitySystem::Update(m_communitySystem, true);

        Red::WeakPtr<Red::Community> community;
        Raw::CommunitySystem::GetCommunity(m_communitySystem, community, communityID);

        if (!community.instance)
            continue;

        for (auto& entry : community.instance->entries)
        {
            if (entry->phases.size > 0)
            {
                Raw::CommunitySystem::SetCommunityPhase(m_communitySystem, communityID, entry->name, entry->phases[0]);
            }
        }

        Raw::CommunitySystem::Update(m_communitySystem, true);
    }

    for (const auto& spawnerID : spawnerIDs)
    {
        Raw::CommunitySystem::DeactivateSpawner(m_communitySystem, spawnerID);
        Raw::CommunitySystem::Update(m_communitySystem, true);

        Raw::CommunitySystem::ResetSpawner(m_communitySystem, spawnerID);
        Raw::CommunitySystem::Update(m_communitySystem, true);
    }

    for (const auto& entityID : entityIDs)
    {
        m_persistencySystem->RemoveDynamicEntityState(entityID);
        m_persistencySystem->ResetPersistentState({entityID}, false);
    }

    for (const auto& persistenceRef : aActivity->persistenceRefs)
    {
        auto objectID = ResolveNodeRef(persistenceRef.objectRef);

        if (!objectID)
            continue;

        m_persistencySystem->ResetPersistentState({objectID, persistenceRef.componentName}, false);
    }

    for (const auto& journalHash : aActivity->journalHashes)
    {
        Red::Handle<Red::gameJournalEntry> entry;
        Raw::JournalManager::GetEntryByHash(m_journalManager, entry, journalHash);

        if (!entry)
            continue;

        Raw::JournalManager::ChangeEntryState(m_journalManager, entry,
                                              Red::gameJournalEntryState::Inactive,
                                              Red::gameJournalNotifyOption::DoNotNotify,
                                              1);
    }

    for (const auto& factID : aActivity->namedFacts)
    {
        m_factManager->ResetFact(factID);
    }

    for (const auto& factID : aActivity->graphFacts)
    {
        m_factManager->ResetGraphFact(factID);
    }

    if (aActivity->lootContainerRef.hash && !aActivity->lootItemIDs.empty())
    {
        auto lootContainerID = ResolveNodeRef(aActivity->lootContainerRef);
        if (lootContainerID)
        {
            for (const auto& itemTDBID : aActivity->lootItemIDs)
            {
                Red::ItemID itemID;
                Red::CallStatic("gameItemID", "FromTDBID", itemID, itemTDBID);
                Red::CallVirtual(m_containerManager, "InjectLoot", lootContainerID, itemID, 1u, nullptr);
            }
        }
    }

    if (aActivity->mappinHash)
    {
        Raw::MappinSystem::SetPoiMappinPhase(m_mappinSystem, aActivity->mappinHash,
                                             Red::gamedataMappinPhase::DiscoveredPhase);
    }

    if (aActivity->phaseGraph)
    {
        Red::QuestContext context{};
        Raw::QuestsSystem::CreateContext(m_questsSystem, &context, 1, 0, -1, -1);

        // {
        //     auto phaseNodePath = aActivity->phaseNodePath;
        //     auto maxDepth = phaseNodePath.size - 1;
        //     for (auto depth = 1; depth <= maxDepth; ++depth)
        //     {
        //         phaseNodePath.size = depth;
        //         auto phaseInstance = m_registry->GetPhaseInstance(phaseNodePath);
        //         context.phaseStack.PushBack(phaseInstance.instance);
        //     }
        // }

        if (!aActivity->resetNodes.empty())
        {
            context.phaseStack.PushBack(aActivity->phaseInstance);

            Red::QuestNodeSocket inputSocket;
            Red::DynArray<Red::QuestNodeSocket> outputSockets;

            for (const auto& resetNode : aActivity->resetNodes)
            {
                Raw::QuestPhaseInstance::ExecuteNode(aActivity->phaseInstance, resetNode, context,
                                                     inputSocket, outputSockets);
            }

            context.phaseStack.Clear();
        }

        if (aActivity->inputNode)
        {
            Red::DynArray<Red::QuestNodeSocket> outputSockets;
            Raw::QuestPhaseInstance::ExequteGraph(aActivity->phaseInstance, context, aActivity->inputNode,
                                                  aActivity->inputSocket, true, outputSockets);
        }
    }

    return OpenWorldActivityResult::OK;
}

Red::EntityID App::OpenWorldSystem::ResolveNodeRef(Red::NodeRef aNodeRef)
{
    // Red::worldGlobalNodeRef context{};
    // Red::ExecuteFunction("worldGlobalNodeID", "GetRoot", &context);
    static const Red::GlobalNodeRef context{Red::FNV1a64("$")};

    Red::GlobalNodeRef resolved{};
    Red::CallGlobal("ResolveNodeRef", resolved, aNodeRef, context);

    return resolved.hash;
}

void App::OpenWorldSystem::PrintActivities(Red::Optional<OpenWorldActivityRequest>& aRequest)
{
    int32_t counter = 0;
    uint32_t gameTime = 0;
    float realTimeMultiplier = 1.0;

    if (aRequest->HasCooldown())
    {
        Red::ScriptGameInstance game;
        Red::CallStatic("ScriptGameInstance", "GetGameTime", gameTime, game);
        realTimeMultiplier = Red::GetFlatValue<float>("timeSystem.settings.realTimeMultiplier");
    }

    for (const auto& activity : m_registry->GetAllActivities())
    {
        auto state = MakeActivityState(activity);

        if (!aRequest->Match(state, gameTime, realTimeMultiplier))
            continue;

        ++counter;
        Red::Log::Debug("[OpenWorldSystem] {} {} {}",
                        counter,
                        activity->name.ToString(),
                        (state.completed ? "completed" : (state.discovered ? "discovered" : "undiscovered")));
    }
}

void App::OpenWorldSystem::DumpActivities()
{
    if (m_registry)
    {
        m_registry->DumpActivities();
    }
}

App::OpenWorldActivityState::OpenWorldActivityState()
    : district(Red::gamedataDistrict::Invalid)
    , area(Red::gamedataDistrict::Invalid)
    , timestamp(0)
    , completed(false)
    , valid(false)
{
}

App::OpenWorldActivityState::OpenWorldActivityState(const Core::SharedPtr<ActivityDefinition>& aSource)
    : name(aSource->name)
    , kind(aSource->kind)
    , district(aSource->district)
    , area(aSource->area)
    , timestamp(0)
    , completed(false)
    , valid(true)
{
}

App::OpenWorldActivityRequest::OpenWorldActivityRequest()
    : cooldown(0)
{
}

bool App::OpenWorldActivityRequest::IsDefault() const
{
    return !kind && cooldown <= 0 && districts.size <= 0;
}

bool App::OpenWorldActivityRequest::HasCooldown() const
{
    return cooldown > 0;
}

bool App::OpenWorldActivityRequest::Match(const App::OpenWorldActivityState& aActivity,
                                          uint32_t aGameTime, float aRealTimeMultiplier) const
{
    if (kind)
    {
        if (aActivity.kind != kind)
        {
            return false;
        }
    }

    if (districts.size > 0)
    {
        bool match = false;
        for (const auto& district : districts)
        {
            if (aActivity.district == district || aActivity.area == district)
            {
                match = true;
                break;
            }
        }
        if (!match)
        {
            return false;
        }
    }

    if (cooldown > 0)
    {
        if (static_cast<float>(aGameTime - aActivity.timestamp) / aRealTimeMultiplier <= cooldown)
        {
            return false;
        }
    }

    return true;
}