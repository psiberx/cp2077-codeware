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
    Red::Handle<Red::gameJournalPointOfInterestMappin> mappinEntry;
    Core::Vector<Red::NodeRef> communityRefs;
    Core::Vector<Red::NodeRef> spawnerRefs;
    Core::Vector<Red::FactID> namedFacts;
    Core::Vector<Red::FactID> graphFacts;
    Core::Vector<Red::JournalEntryHash> journalHashes;
    Core::Vector<PersistentStateRef> persistenceRefs;
    Core::Vector<Red::TweakDBID> lootItemIDs;
    Red::NodeRef lootContainerRef;

    Red::questPhaseInstance* phaseInstance;
    Red::WeakHandle<Red::questGraphDefinition> phaseGraph;
    Red::QuestNodePath phaseNodePath;
    Red::QuestNodeKey phaseNodeKey;
    Red::WeakHandle<Red::questNodeDefinition> inputNode;
    Red::QuestNodeSocket inputSocket;
    Red::QuestNodeKey inputNodeKey;
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
    void DumpActivities();

    Red::WeakHandle<Red::questPhaseInstance> GetPhaseInstance(Red::QuestNodeKey aPhasePath);

protected:
    void OnBootstrap() override;
    static void OnPhasePreloadCheck(bool& aPreload, void* aLoader, const Red::QuestNodePath& aPhaseNodePath);
    static void OnInitializePhase(Red::questPhaseInstance* aPhase, Red::QuestContext& aContext,
                                  const Red::Handle<Red::questQuestPhaseResource>& aPhaseResource,
                                  Red::Handle<Red::questGraphDefinition>& aPhaseGraph,
                                  const Red::QuestNodePath& aParentPath, Red::NodeID aPhaseNodeID);

    static bool RegisterCrimeActivity(QuestPhaseGraphAccessor& aPhaseGraphAccessor,
                                      Red::questPhaseInstance* aPhase,
                                      Red::Handle<Red::questGraphDefinition>& aPhaseGraph,
                                      const Red::QuestNodePath& aParentPath, Red::NodeID aPhaseNodeID);
    static bool RegisterCyberpsychoActivity(QuestPhaseGraphAccessor& aPhaseGraphAccessor,
                                            Red::questPhaseInstance* aPhase,
                                            const Red::Handle<Red::questGraphDefinition>& aPhaseGraph,
                                            const Red::QuestNodePath& aParentPath, Red::NodeID aPhaseNodeID);

    static Red::QuestNodeKey MakePhaseNodeKey(Red::QuestNodePath aParentPath, Red::NodeID aPhaseNodeID,
                                              Red::NodeID aInputNodeID = -1);
    static Red::CName ExtractMinorActivityName(const Red::CString& aJournalPath);
    static bool IsMinorActivityRelatedFact(const Red::CString& aFactName);
    static bool IsCombatActivityVariant(Red::gamedataMappinVariant aVariant);

private:
    inline static Core::Map<Red::CName, Core::SharedPtr<ActivityDefinition>> s_activities;
    inline static Core::Map<uint64_t, Red::WeakHandle<Red::questPhaseInstance>> s_phaseInstances;
    inline static Red::QuestNodePath s_minorActivitiesRootPhasePath;
};
}
