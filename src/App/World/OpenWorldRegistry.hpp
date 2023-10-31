#pragma once

#include "Core/Foundation/Feature.hpp"
#include "Core/Hooking/HookingAgent.hpp"
#include "Core/Logging/LoggingAgent.hpp"
#include "Red/JournalManager.hpp"
#include "Red/QuestsSystem.hpp"

namespace App
{
struct PersistentStateRef
{
    Red::NodeRef objectRef;
    Red::CName component;
};

struct MinorActivityData
{
    Red::CName name;

    Red::JournalEntryHash mappinHash;
    Core::Vector<Red::NodeRef> communityRefs;
    Core::Vector<Red::NodeRef> spawnerRefs;
    Core::Vector<Red::FactHash> factHashes;
    Core::Vector<Red::JournalEntryHash> journalHashes;
    Core::Vector<PersistentStateRef> persistenceRefs;

    Red::questPhaseInstance* phaseInstance;
    Red::Handle<Red::questGraphDefinition> phaseGraph;
    Red::WeakHandle<Red::questNodeDefinition> inputNode;
    Red::QuestNodeSocket inputSocket;
    Red::PhaseNodePath inputNodePath;
};

class OpenWorldRegistry
    : public Core::Feature
    , public Core::HookingAgent
    , public Core::LoggingAgent
{
public:
    Core::Vector<Core::SharedPtr<MinorActivityData>> GetAllMinorActivities();
    Core::Vector<Red::CName> GetAllMinorActivityNames();
    Core::SharedPtr<MinorActivityData> FindMinorActivity(Red::CName aName);

protected:
    void OnBootstrap() override;
    void OnInitializePhase(Red::questPhaseInstance* aPhase, uint64_t a2,
                           const Red::Handle<Red::questQuestPhaseResource>& aPhaseResource,
                           const Red::Handle<Red::questGraphDefinition>& aPhaseGraph,
                           const Red::NodePath& aParentPath,
                           Red::NodeID aNodeID);

    static Red::PhaseNodePath MakePhaseNodePath(Red::NodePath aParentPath, Red::NodeID aPhaseNodeID,
                                                Red::NodeID aInputNodeID);
    static Red::CName ExtractMinorActivityName(const Red::CString& aJournalPath);
    static bool IsMinorActivityRelatedFact(const Red::CString& aFactName);

private:
    Core::Map<Red::CName, Core::SharedPtr<MinorActivityData>> m_activities;
};
}
