#include "OpenWorldRegistry.hpp"
#include "App/Quest/QuestPhaseGraphAccessor.hpp"

void App::OpenWorldRegistry::OnBootstrap()
{
    HookAfter<Raw::PhaseInstance::Initialize>(&OpenWorldRegistry::OnInitializePhase);
}

void App::OpenWorldRegistry::OnInitializePhase(Red::questPhaseInstance* aPhase, uint64_t a2,
                                               const Red::Handle<Red::questQuestPhaseResource>& aPhaseResource,
                                               const Red::Handle<Red::questGraphDefinition>& aPhaseGraph,
                                               const Red::NodePath& aParentPath, Red::NodeID aPhaseNodeID)
{
    if (!aPhaseResource)
        return;

    QuestPhaseGraphAccessor graphAccessor(aPhaseGraph);
    auto mappinPhase = graphAccessor.FindCompletedMappinPhase();

    if (!mappinPhase)
        return;

    auto activityName = ExtractMinorActivityName(mappinPhase->path->realPath);

    if (!activityName)
        return;

    auto communityActivations = graphAccessor.FindCommunityActivations();

    if (communityActivations.empty())
        return;

    auto journalEntries = graphAccessor.FindJournalEntries();
    auto factChanges = graphAccessor.FindFactChanges();
    auto areaLinks = graphAccessor.FindAreaLinks();

    auto minorActivity = Core::MakeShared<MinorActivityData>();
    minorActivity->name = activityName;
    minorActivity->mappinHash = Red::Murmur3_32(mappinPhase->path->realPath.c_str());
    minorActivity->phaseNodePath = MakePhaseNodePath(aParentPath, aPhaseNodeID);

    for (const auto& communityActivation : communityActivations)
    {
        minorActivity->communityRefs.push_back(communityActivation->spawnerReference);
    }

    for (const auto& areaLink : areaLinks)
    {
        if (areaLink->PSClassName)
        {
            minorActivity->persistenceRefs.push_back({areaLink->objectRef.reference, areaLink->componentName});
        }
    }

    for (const auto& journalEntry : journalEntries)
    {
        if (journalEntry->type->path->className != Red::GetTypeName<Red::gameJournalPointOfInterestMappin>())
        {
            minorActivity->journalHashes.push_back(Red::Murmur3_32(journalEntry->type->path->realPath.c_str()));
        }
    }

    for (const auto& factChange : factChanges)
    {
        if (IsMinorActivityRelatedFact(factChange->factName))
        {
            minorActivity->factHashes.push_back(Red::FNV1a32(factChange->factName.c_str()));
        }
    }

    minorActivity->inputSockets.PushBack(graphAccessor.GetInputSocketName());

    m_activities.emplace(minorActivity->name, std::move(minorActivity));

#ifndef NDEBUG
    LogDebug("Minor Activity Discovered: {} {}", activityName.ToString(), aPhaseResource->path.hash);
#endif
}

Red::PhaseNodePath App::OpenWorldRegistry::MakePhaseNodePath(Red::NodePath aParentPath, Red::NodeID aNodeID)
{
    aParentPath.PushBack(aNodeID);
    return {aParentPath};
}

Red::CName App::OpenWorldRegistry::ExtractMinorActivityName(const Red::CString& aJournalPath)
{
    constexpr auto AddonPrefix = "ep1/";
    constexpr auto AddonPrefixLength = std::char_traits<char>::length(AddonPrefix);
    constexpr auto MinorActivityPrefix = "points_of_interest/minor_activities/";
    constexpr auto MinorActivityPrefixLength = std::char_traits<char>::length(MinorActivityPrefix);

    std::string_view path(aJournalPath.c_str());

    if (path.starts_with(AddonPrefix))
    {
        path.remove_prefix(AddonPrefixLength);
    }

    if (path.starts_with(MinorActivityPrefix))
    {
        path.remove_prefix(MinorActivityPrefixLength);
        return Red::CNamePool::Add(path.data());
    }

    return {};
}

bool App::OpenWorldRegistry::IsMinorActivityRelatedFact(const Red::CString& aFactName)
{
    constexpr auto MinorActivityPrefix = "ma_";
    constexpr auto TokenSuffix = "_token";
    constexpr auto TutorialSuffix = "_tutorial";

    std::string_view name(aFactName.c_str());
    return name.starts_with(MinorActivityPrefix) && !name.ends_with(TokenSuffix) && !name.ends_with(TutorialSuffix);
}

Core::Vector<Core::SharedPtr<App::MinorActivityData>> App::OpenWorldRegistry::GetAllMinorActivities()
{
    Core::Vector<Core::SharedPtr<App::MinorActivityData>> activities;

    for (const auto& [_, activity] : m_activities)
    {
        activities.push_back(activity);
    }

    return activities;
}

Core::Vector<Red::CName> App::OpenWorldRegistry::GetAllMinorActivityNames()
{
    Core::Vector<Red::CName> activities;

    for (const auto& [name, _] : m_activities)
    {
        activities.push_back(name);
    }

    return activities;
}

Core::SharedPtr<App::MinorActivityData> App::OpenWorldRegistry::FindMinorActivity(Red::CName aName)
{
    const auto& it = m_activities.find(aName);

    if (it == m_activities.end())
        return {};

    return it.value();
}
