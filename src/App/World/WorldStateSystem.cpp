#include "WorldStateSystem.hpp"
#include "Core/Facades/Container.hpp"
#include "Red/CommunitySystem.hpp"
#include "Red/NodeRef.hpp"
#include "Red/StreamingWorld.hpp"

void App::WorldStateSystem::OnWorldAttached(Red::world::RuntimeScene*)
{
    m_communitySystem = Red::GetGameSystem<Red::gameICommunitySystem>();
    m_questsSystem = Red::GetGameSystem<Red::questIQuestsSystem>();
    m_factManager = Raw::QuestsSystem::FactManager::Ref(m_questsSystem);

    m_questPhaseRegistry = Core::Resolve<QuestPhaseRegistry>();
    m_questPhaseExecutor = Core::MakeUnique<QuestPhaseExecutor>(m_questPhaseRegistry, m_questsSystem);

    m_ready = true;
}

void App::WorldStateSystem::OnAfterWorldDetach()
{
    m_ready = false;
}

bool App::WorldStateSystem::IsReady()
{
    return m_ready && m_questPhaseRegistry->PhasesInitialized();
}

Red::Handle<Red::worldStreamingWorld> App::WorldStateSystem::GetStreamingWorld()
{
    auto streamingSystem = Red::GetRuntimeSystem<Red::worldRuntimeSystemWorldStreaming>();
    return Raw::RuntimeSystemWorldStreaming::StreamingWorld::Ref(streamingSystem);
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

void App::WorldStateSystem::ToggleNode(Red::NodeRef aNodeRef, bool aState)
{
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
