#pragma once

#include "App/Quest/QuestPhaseGraphAccessor.hpp"
#include "Core/Foundation/Feature.hpp"
#include "Core/Hooking/HookingAgent.hpp"
#include "Core/Logging/LoggingAgent.hpp"
#include "Red/JournalManager.hpp"
#include "Red/QuestsSystem.hpp"

namespace App
{
struct CommunityRef
{
    Red::NodeRef objectRef;
    Red::CName entryName;
};

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
    Core::Vector<Red::TweakDBID> lootItemIDs;
    Red::NodeRef lootContainerRef;
    Red::NodeRef securitySystemRef;

    Core::Vector<CommunityRef> communityRefs;
    Core::Vector<Red::NodeRef> spawnerRefs;
    Core::Vector<Red::FactID> namedFacts;
    Core::Vector<Red::FactID> graphFacts;
    Core::Vector<Red::JournalEntryHash> journalHashes;
    Core::Vector<PersistentStateRef> persistenceRefs;

    Red::questPhaseInstance* phaseInstance;
    Red::WeakHandle<Red::questGraphDefinition> phaseGraph;
    Red::WeakHandle<Red::questQuestPhaseResource> phaseResource;
    Red::QuestNodePath phaseNodePath;
    Red::QuestNodeKey phaseNodeKey;
    Red::WeakHandle<Red::questNodeDefinition> inputNode;
    Red::QuestNodeSocket inputSocket;
    Red::QuestNodeKey inputNodeKey;
    Core::Vector<Red::Handle<Red::questNodeDefinition>> resetNodes;
};

class QuestPhaseRegistry
    : public Core::Feature
    , public Core::HookingAgent
    , public Core::LoggingAgent
{
public:
    bool PhasesInitialized();
    Red::questPhaseInstance* GetPhaseInstance(Red::QuestNodeKey aPhasePath);

    bool ActivitiesInitialized();
    void InitializeActivities();
    Core::Vector<Core::SharedPtr<ActivityDefinition>> GetAllActivities();
    Core::Vector<Red::CName> GetAllActivityNames();
    Core::SharedPtr<ActivityDefinition> FindActivity(Red::CName aName);
    void DumpActivities();

protected:
    void OnBootstrap() override;
    static void OnPhasePreloadCheck(bool& aPreload, void* aLoader, const Red::QuestNodePath& aPhaseNodePath);
    static void OnInitializePhase(Red::questPhaseInstance* aPhase, Red::QuestContext& aContext,
                                  const Red::Handle<Red::questQuestPhaseResource>& aPhaseResource,
                                  Red::Handle<Red::questGraphDefinition>& aPhaseGraph,
                                  const Red::QuestNodePath& aParentPath, Red::NodeID aPhaseNodeID);

    static void ApplyActivityBugfixes(App::QuestPhaseGraphAccessor& aPhaseGraphAccessor,
                                      const Red::Handle<Red::questQuestPhaseResource>& aPhaseResource,
                                      Red::Handle<Red::questGraphDefinition>& aPhaseGraph);
    static bool RegisterCrimeActivity(QuestPhaseGraphAccessor& aPhaseGraphAccessor,
                                      Red::questPhaseInstance* aPhase,
                                      const Red::Handle<Red::questQuestPhaseResource>& aPhaseResource,
                                      Red::Handle<Red::questGraphDefinition>& aPhaseGraph,
                                      const Red::QuestNodePath& aPhaseNodePath);
    static bool RegisterCyberpsychoActivity(QuestPhaseGraphAccessor& aPhaseGraphAccessor,
                                            Red::questPhaseInstance* aPhase,
                                            const Red::Handle<Red::questGraphDefinition>& aPhaseGraph,
                                            const Red::QuestNodePath& aParentPath, Red::NodeID aPhaseNodeID);
    static void GenerateResetNodes(QuestPhaseGraphAccessor& aPhaseGraphAccessor,
                                   const Red::Handle<Red::questQuestPhaseResource>& aPhaseResource,
                                   Core::Vector<Red::Handle<Red::questNodeDefinition>>& aResetNodes);

    static Red::CName ExtractMinorActivityName(const Red::CString& aJournalPath);
    static bool IsMinorActivityRelatedFact(const Red::CString& aFactName);
    static bool IsCombatActivityVariant(Red::gamedataMappinVariant aVariant);

private:
    inline static std::shared_mutex s_phasesLock;
    inline static Core::Map<uint64_t, Red::WeakHandle<Red::questPhaseInstance>> s_phases;
    inline static bool s_phasesReady;

    inline static std::shared_mutex s_activitiesLock;
    inline static Core::Map<Red::CName, Core::SharedPtr<ActivityDefinition>> s_activities;
    inline static Red::QuestNodePath s_minorActivitiesRootPhasePath;
    inline static Red::QuestNodePath s_communitiesRootPhasePath;
    inline static bool s_activitiesReady;
};
}
