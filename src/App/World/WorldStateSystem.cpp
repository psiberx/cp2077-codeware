#include "WorldStateSystem.hpp"
#if defined(__APPLE__)
#include "MacDiag.hpp"
#include "MacEngine.hpp"
#endif
#include "App/World/CommunityWrapper.hpp"
#include "Core/Facades/Container.hpp"
#include "Red/CommunitySystem.hpp"
#include "Red/NodeRef.hpp"
#include "Red/StreamingWorld.hpp"

#include <cstdio>

void App::WorldStateSystem::OnWorldAttached(Red::world::RuntimeScene*)
{
#if defined(__APPLE__)
    if (!Red::MacSystemEnabled("WorldStateSystem"))
    {
        Red::MacSystemOff("WorldStateSystem", "switched off with CODEWARE_MAC_SYSTEMS_OFF");
        return;
    }
#endif
    m_communitySystem = Red::GetGameSystem<Red::gameICommunitySystem>();
    m_questsSystem = Red::GetGameSystem<Red::questIQuestsSystem>();
#if defined(__APPLE__)
    // R21. The quest and community systems are not all present in the menu scene; the system stays off until a world attach finds them.
    if (!m_communitySystem || !m_questsSystem)
    {
        MAC_DIAG( "[cw] R21 WorldStateSystem waits: community=%p quests=%p\n", static_cast<void*>(m_communitySystem),
                     static_cast<void*>(m_questsSystem));
        Red::MacSystemOff("WorldStateSystem", "the community or quests system is not present at this world attach");
        return;
    }
#endif
    m_factManager = Raw::QuestsSystem::FactManager::Ref(m_questsSystem);

    m_questPhaseRegistry = Core::Resolve<QuestPhaseRegistry>();
    m_questPhaseExecutor = Core::MakeUnique<QuestPhaseExecutor>(m_questPhaseRegistry, m_questsSystem);

    m_ready = true;
#if defined(__APPLE__)
    MAC_DIAG( "[cw] R21 WorldStateSystem ready quests=%p community=%p factManager=%p\n", static_cast<void*>(m_questsSystem),
                 static_cast<void*>(m_communitySystem), static_cast<void*>(m_factManager));
#endif
}

void App::WorldStateSystem::OnAfterWorldDetach()
{
    m_ready = false;
}

bool App::WorldStateSystem::IsReady() const
{
    return m_ready;
}

Red::Handle<Red::worldStreamingWorld> App::WorldStateSystem::GetStreamingWorld()
{
    auto streamingSystem = Red::GetRuntimeSystem<Red::worldRuntimeSystemWorldStreaming>();
    return Raw::RuntimeSystemWorldStreaming::StreamingWorld::Ref(streamingSystem);
}

Red::Handle<App::CommunityWrapper> App::WorldStateSystem::GetCommunity(Red::NodeRef aNodeRef)
{
    if (!m_communitySystem)
        return {};

    auto communityID = Red::ResolveNodeRef(aNodeRef);
    if (!communityID)
        return {};

    Red::WeakPtr<Red::Community> communityWeak;
    Raw::CommunitySystem::GetCommunity(m_communitySystem, communityWeak, communityID);

    auto community = communityWeak.Lock();
    if (!community)
        return {};

    return Red::MakeHandle<CommunityWrapper>(community);
}

void App::WorldStateSystem::ActivateCommunity(Red::NodeRef aNodeRef, Red::Optional<Red::CName> aEntryName)
{
    auto communityID = Red::ResolveNodeRef(aNodeRef);

    if (!communityID)
        return;

    Raw::CommunitySystem::ActivateCommunity(m_communitySystem, communityID, aEntryName);
    Raw::CommunitySystem::Update(m_communitySystem, true);
}

void App::WorldStateSystem::DeactivateCommunity(Red::NodeRef aNodeRef, Red::Optional<Red::CName> aEntryName)
{
    auto communityID = Red::ResolveNodeRef(aNodeRef);

    if (!communityID)
        return;

    Raw::CommunitySystem::DeactivateCommunity(m_communitySystem, communityID, aEntryName);
    Raw::CommunitySystem::Update(m_communitySystem, true);
}

void App::WorldStateSystem::ResetCommunity(Red::NodeRef aNodeRef)
{
    auto communityID = Red::ResolveNodeRef(aNodeRef);

    if (!communityID)
        return;

    Raw::CommunitySystem::ResetCommunity(m_communitySystem, communityID, {});
    Raw::CommunitySystem::Update(m_communitySystem, true);
}

void App::WorldStateSystem::SetCommunityPhase(Red::NodeRef aNodeRef, Red::CName aEntryName, Red::CName aPhaseName)
{
    auto communityID = Red::ResolveNodeRef(aNodeRef);

    if (!communityID)
        return;

    Raw::CommunitySystem::SetCommunityPhase(m_communitySystem, communityID, aEntryName, aPhaseName);
    Raw::CommunitySystem::Update(m_communitySystem, true);
}

Red::Handle<App::PopulationSpawnerWrapper> App::WorldStateSystem::GetPopulationSpawner(Red::NodeRef aNodeRef)
{
    if (!m_communitySystem)
        return {};

    auto spawnerID = Red::ResolveNodeRef(aNodeRef);
    if (!spawnerID)
        return {};

    Red::WeakPtr<Red::Spawner> spawnerWeak;
    Raw::CommunitySystem::GetSpawner(m_communitySystem, spawnerWeak, spawnerID);

    auto spawner = spawnerWeak.Lock();
    if (!spawner)
        return {};

    return Red::MakeHandle<PopulationSpawnerWrapper>(spawner);
}

void App::WorldStateSystem::ActivatePopulationSpawner(Red::NodeRef aNodeRef)
{
    auto spawnerID = Red::ResolveNodeRef(aNodeRef);
    if (!spawnerID)
        return;

    Raw::CommunitySystem::ActivateSpawner(m_communitySystem, spawnerID);
    Raw::CommunitySystem::Update(m_communitySystem, true);
}

void App::WorldStateSystem::DeactivatePopulationSpawner(Red::NodeRef aNodeRef)
{
    auto spawnerID = Red::ResolveNodeRef(aNodeRef);
    if (!spawnerID)
        return;

    Raw::CommunitySystem::DeactivateSpawner(m_communitySystem, spawnerID);
    Raw::CommunitySystem::Update(m_communitySystem, true);
}

void App::WorldStateSystem::ResetPopulationSpawner(Red::NodeRef aNodeRef)
{
    auto spawnerID = Red::ResolveNodeRef(aNodeRef);
    if (!spawnerID)
        return;

    Raw::CommunitySystem::ResetSpawner(m_communitySystem, spawnerID);
    Raw::CommunitySystem::Update(m_communitySystem, true);
}

void App::WorldStateSystem::ToggleNode(Red::NodeRef aNodeRef, bool aState)
{
    if (!IsReady())
        return;

    auto resetNodeType = Red::MakeHandle<Red::questShowWorldNode_NodeType>();
    resetNodeType->objectRef = aNodeRef;
    resetNodeType->show = aState;

    auto resetNode = Red::MakeHandle<Red::questWorldDataManagerNodeDefinition>();
    resetNode->id = 0;
    resetNode->type = resetNodeType;

    m_questPhaseExecutor->ExecuteNode(resetNode);
}

void App::WorldStateSystem::ToggleVariant(Red::NodeRef aNodeRef, Red::CName aVariant, bool aState)
{
    if (!IsReady())
        return;

    Red::questVariantState variantState;
    variantState.name = aVariant;
    variantState.show = aState;

    Red::questTogglePrefabVariant_NodeTypeParams variantParam{};
    variantParam.prefabNodeRef = aNodeRef;
    variantParam.variantStates.PushBack(variantState);

    auto resetNodeType = Red::MakeHandle<Red::questTogglePrefabVariant_NodeType>();
    resetNodeType->params.PushBack(variantParam);

    auto resetNode = Red::MakeHandle<Red::questWorldDataManagerNodeDefinition>();
    resetNode->id = 0;
    resetNode->type = resetNodeType;

    m_questPhaseExecutor->ExecuteNode(resetNode);
}
