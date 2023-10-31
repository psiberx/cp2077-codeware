#include "OpenWorldSystem.hpp"
#include "App/Quest/QuestPhaseGraphAccessor.hpp"
#include "Core/Facades/Container.hpp"
#include "Red/CommunitySystem.hpp"
#include "Red/MappinSystem.hpp"

void App::OpenWorldSystem::OnWorldAttached(Red::world::RuntimeScene*)
{
    m_registry = Core::Resolve<OpenWorldRegistry>();

    m_communitySystem = Red::GetGameSystem<Red::gameICommunitySystem>();
    m_populationSystem = Red::GetGameSystem<Red::gameIPopulationSystem>();
    m_persistencySystem = Red::GetGameSystem<Red::gameIPersistencySystem>();
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

bool App::OpenWorldSystem::ReactivateMinorActivity(Red::CName aName)
{
    const auto& activity = m_registry->FindMinorActivity(aName);

    if (!activity)
        return false;

    return ProcessMinorActivityReactivation(activity);
}

bool App::OpenWorldSystem::ReactivateMinorActivities()
{
    bool success = false;

    for (const auto& activity : m_registry->GetAllMinorActivities())
    {
        if (ProcessMinorActivityReactivation(activity))
        {
            success = true;
        }
    }

    return success;
}

bool App::OpenWorldSystem::IsMinorActivityCompleted(const Core::SharedPtr<App::MinorActivityData>& aActivity)
{
    auto phase = Raw::MappinSystem::GetPoiMappinPhase(m_mappinSystem, aActivity->mappinHash);
    return phase == Red::gamedataMappinPhase::CompletedPhase;
}

bool App::OpenWorldSystem::ProcessMinorActivityReactivation(const Core::SharedPtr<App::MinorActivityData>& aActivity)
{
    if (!IsMinorActivityCompleted(aActivity))
        return false;

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
            return false;
    }

    Red::QuestContext context{};
    Raw::QuestsSystem::CreateContext(m_questsSystem, &context, 1, 0, 1000003, -1);

    {
        context.phaseStack.PushBack(aActivity->phaseInstance);

        Red::QuestNodeSocket inputSocket;
        Red::DynArray<Red::QuestNodeSocket> outputSockets;

        QuestPhaseGraphAccessor graphAccessor(aActivity->phaseGraph);

        for (const auto& node : graphAccessor.GetNodesOfType<Red::questWorldDataManagerNodeDefinition>())
        {
            if (const auto& nodeType = Red::Cast<Red::questTogglePrefabVariant_NodeType>(node->type))
            {
                for (auto& param : nodeType->params)
                {
                    for (auto& state : param.variantStates)
                    {
                        state.show = !state.show;
                    }
                }

                Raw::PhaseInstance::ExecuteNode(aActivity->phaseInstance, node, context, inputSocket, outputSockets);

                for (auto& param : nodeType->params)
                {
                    for (auto& state : param.variantStates)
                    {
                        state.show = !state.show;
                    }
                }
            }
        }

        context.phaseStack.Clear();
    }

    for (const auto& communityID : communityIDs)
    {
        Raw::CommunitySystem::DeactivateCommunity(m_communitySystem, communityID, {});
        Raw::CommunitySystem::Update(m_communitySystem, true);

        Raw::CommunitySystem::ResetCommunity(m_communitySystem, communityID, {});
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
    }

    for (const auto& persistenceRef : aActivity->persistenceRefs)
    {
        auto objectID = ResolveNodeRef(persistenceRef.objectRef);

        if (!objectID)
            continue;

        m_persistencySystem->ResetPersistentState({objectID, persistenceRef.component}, true);
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

    for (const auto& factHash : aActivity->factHashes)
    {
        m_factManager->SetFact(factHash, 0);
    }

    Raw::MappinSystem::SetPoiMappinPhase(m_mappinSystem, aActivity->mappinHash,
                                         Red::gamedataMappinPhase::DiscoveredPhase);

    {
        Red::DynArray<Red::QuestNodeSocket> outputSockets;
        Raw::PhaseInstance::ExequteSequence(aActivity->phaseInstance,
                                            context,
                                            aActivity->inputNode,
                                            aActivity->inputSocket,
                                            true,
                                            outputSockets);
    }

    return true;
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
