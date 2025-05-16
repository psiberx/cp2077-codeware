#include "OpenWorldSystem.hpp"
#include "Core/Facades/Container.hpp"
#include "Core/Facades/Log.hpp"
#include "Red/CommunitySystem.hpp"
#include "Red/JournalManager.hpp"
#include "Red/MappinSystem.hpp"
#include "Red/NodeRef.hpp"
#include "Red/TweakDB.hpp"

void App::OpenWorldSystem::OnWorldAttached(Red::world::RuntimeScene*)
{
    m_communitySystem = Red::GetGameSystem<Red::gameICommunitySystem>();
    m_populationSystem = Red::GetGameSystem<Red::gameIPopulationSystem>();
    m_persistencySystem = Red::GetGameSystem<Red::gameIPersistencySystem>();
    m_containerManager = Red::GetGameSystem<Red::gameIContainerManager>();
    m_journalManager = Red::GetGameSystem<Red::gameIJournalManager>();
    m_mappinSystem = Red::GetGameSystem<Red::gamemappinsIMappinSystem>();
    m_questsSystem = Red::GetGameSystem<Red::questIQuestsSystem>();
    m_factManager = Raw::QuestsSystem::FactManager::Ref(m_questsSystem);

    m_questPhaseRegistry = Core::Resolve<QuestPhaseRegistry>();
    m_questPhaseExecutor = Core::MakeUnique<QuestPhaseExecutor>(m_questPhaseRegistry, m_questsSystem);

    m_ready = true;
}

void App::OpenWorldSystem::OnAfterWorldDetach()
{
    m_ready = false;
}

bool App::OpenWorldSystem::OnGameRestored()
{
    m_questPhaseRegistry->InitializeActivities();

    return true;
}

bool App::OpenWorldSystem::IsReady()
{
    return m_ready && m_questPhaseRegistry->ActivitiesInitialized();
}

App::OpenWorldActivityState App::OpenWorldSystem::GetActivity(Red::CName aName)
{
    const auto& activity = m_questPhaseRegistry->FindActivity(aName);

    if (!activity)
        return {};

    return MakeActivityState(activity);
}

Red::DynArray<App::OpenWorldActivityState> App::OpenWorldSystem::GetActivities()
{
    Red::DynArray<OpenWorldActivityState> states;

    for (const auto& activity : m_questPhaseRegistry->GetAllActivities())
    {
        states.EmplaceBack(MakeActivityState(activity));
    }

    return states;
}

App::OpenWorldActivityResult App::OpenWorldSystem::StartActivity(Red::CName aName, Red::Optional<bool> aForce)
{
    const auto& activity = m_questPhaseRegistry->FindActivity(aName);

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

    for (const auto& activity : m_questPhaseRegistry->GetAllActivities())
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
        auto communityID = Red::ResolveEntityID(communityRef.objectRef);

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
        auto spawnerID = Red::ResolveEntityID(spawnerRef);

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
        auto objectID = Red::ResolveEntityID(persistenceRef.objectRef);

        if (!objectID)
            continue;

        Red::Handle<Red::Entity> entity;
        Red::ScriptGameInstance game;
        Red::CallStatic("ScriptGameInstance", "FindEntityByID", entity, game, objectID);

        if (entity)
            return OpenWorldActivityResult::StillSpawned;

        // TODO: Use node registry for static nodes?
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
        auto objectID = Red::ResolveEntityID(persistenceRef.objectRef);

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

    for (const auto& factID : aActivity->graphFacts)
    {
        m_factManager->ResetGraphFact(factID);
    }

    if (aActivity->lootContainerRef.hash && !aActivity->lootItemIDs.empty())
    {
        auto lootContainerID = Red::ResolveEntityID(aActivity->lootContainerRef);
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
        if (!aActivity->resetNodes.empty())
        {
            m_questPhaseExecutor->ExecuteNodes(aActivity->resetNodes, aActivity->phaseInstance);
        }

        if (aActivity->inputNode)
        {
            m_questPhaseExecutor->ExecutePath(aActivity->phaseNodePath, aActivity->inputNodeKey.nodeID, aActivity->inputSocket.name);
            // m_questNodeExecutor->ExecuteGraph(aActivity->inputNode, aActivity->inputSocket, aActivity->phaseInstance);
        }
    }

    return OpenWorldActivityResult::OK;
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

    for (const auto& activity : m_questPhaseRegistry->GetAllActivities())
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
    if (m_questPhaseRegistry)
    {
        m_questPhaseRegistry->DumpActivities();
    }
}

App::OpenWorldActivityState::OpenWorldActivityState()
    : district(Red::gamedataDistrict::Invalid)
    , area(Red::gamedataDistrict::Invalid)
    , timestamp(0)
    , completed(false)
    , discovered(false)
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
    , discovered(false)
    , valid(true)
{
}

App::OpenWorldActivityRequest::OpenWorldActivityRequest()
    : cooldown(0)
    , force(false)
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
