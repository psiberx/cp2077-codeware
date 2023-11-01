#pragma once

#include "App/Quest/QuestPhaseGraphAccessor.hpp"
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
    Red::CName componentName;
    Red::CName persistentStateType;
};

struct ActivityDefinition
{
    Red::CName name;
    Red::CName kind; // ncpd cyberpsycho

    Red::CName title;
    Red::CName description;
    Red::gamedataDistrict district;
    Red::gamedataDistrict area;

    Red::JournalEntryHash mappinHash;
    Red::Handle<Red::gameJournalEntry> mappinEntry;
    Core::Vector<Red::NodeRef> communityRefs;
    Core::Vector<Red::NodeRef> spawnerRefs;
    Core::Vector<Red::FactID> namedFacts;
    Core::Vector<Red::FactID> graphFacts;
    Core::Vector<Red::JournalEntryHash> journalHashes;
    Core::Vector<PersistentStateRef> persistenceRefs;
    Core::Vector<Red::TweakDBID> lootItemIDs;
    Red::NodeRef lootContainerRef;

    Red::questPhaseInstance* phaseInstance;
    Red::Handle<Red::questGraphDefinition> phaseGraph;
    Red::PhaseNodePath phaseNodePath;
    Red::WeakHandle<Red::questNodeDefinition> inputNode;
    Red::QuestNodeSocket inputSocket;
    Red::PhaseNodePath inputNodePath;
    Core::Vector<Red::Handle<Red::questNodeDefinition>> resetNodes;
};

class OpenWorldRegistry
    : public Core::Feature
    , public Core::HookingAgent
    , public Core::LoggingAgent
{
public:
    Core::Vector<Core::SharedPtr<ActivityDefinition>> GetAllActivities();
    Core::Vector<Red::CName> GetAllActivityNames();
    Core::SharedPtr<ActivityDefinition> FindActivity(Red::CName aName);

protected:
    void OnBootstrap() override;
    void OnInitializePhase(Red::questPhaseInstance* aPhase, Red::QuestContext& aContext,
                           const Red::Handle<Red::questQuestPhaseResource>& aPhaseResource,
                           const Red::Handle<Red::questGraphDefinition>& aPhaseGraph,
                           const Red::NodePath& aParentPath, Red::NodeID aPhaseNodeID);

    bool RegisterCrimeActivity(QuestPhaseGraphAccessor& aPhaseGraphAccessor, Red::questPhaseInstance* aPhase,
                               const Red::Handle<Red::questGraphDefinition>& aPhaseGraph,
                               const Red::NodePath& aParentPath, Red::NodeID aPhaseNodeID);

    bool RegisterCyberpsychoActivity(QuestPhaseGraphAccessor& aPhaseGraphAccessor, Red::questPhaseInstance* aPhase,
                                     const Red::Handle<Red::questGraphDefinition>& aPhaseGraph,
                                     const Red::NodePath& aParentPath, Red::NodeID aPhaseNodeID);

    static Red::PhaseNodePath MakePhaseNodePath(Red::NodePath aParentPath, Red::NodeID aPhaseNodeID,
                                                Red::NodeID aInputNodeID = -1);
    static Red::CName ExtractMinorActivityName(const Red::CString& aJournalPath);
    static bool IsMinorActivityRelatedFact(const Red::CString& aFactName);

private:
    Core::Map<Red::CName, Core::SharedPtr<ActivityDefinition>> m_activities;
};
}
