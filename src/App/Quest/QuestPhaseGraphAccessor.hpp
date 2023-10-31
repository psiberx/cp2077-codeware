#pragma once

namespace App
{
class QuestPhaseGraphAccessor
{
public:
    explicit QuestPhaseGraphAccessor(const Red::Handle<Red::questGraphDefinition>& aPhaseGraph)
    {
        CollectNodes(aPhaseGraph);
    }

    template<class T>
    inline Core::Vector<Red::Handle<T>>& GetNodesOfType()
    {
        return *reinterpret_cast<Core::Vector<Red::Handle<T>>*>(&m_nodesByType[Red::GetTypeName<T>()]);
    }

    inline Red::Handle<Red::questJournalChangeMappinPhase_NodeType> FindCompletedMappinPhase()
    {
        for (const auto& journalNode : GetNodesOfType<Red::questJournalNodeDefinition>())
        {
            if (const auto& mappinPhaseType = Red::Cast<Red::questJournalChangeMappinPhase_NodeType>(journalNode->type))
            {
                if (mappinPhaseType->phase == Red::gamedataMappinPhase::CompletedPhase)
                {
                    return mappinPhaseType;
                }
            }
        }

        return {};
    }

    inline Core::Vector<Red::Handle<Red::questCommunityTemplate_NodeType>> FindCommunities()
    {
        Core::Vector<Red::Handle<Red::questCommunityTemplate_NodeType>> communities;

        for (const auto& spawnNode : GetNodesOfType<Red::questSpawnManagerNodeDefinition>())
        {
            for (const auto& spawnAction : spawnNode->actions)
            {
                if (const auto& communityType = Red::Cast<Red::questCommunityTemplate_NodeType>(spawnAction.type))
                {
                    if (communityType->action == Red::populationSpawnerObjectCtrlAction::Activate ||
                        communityType->action == Red::populationSpawnerObjectCtrlAction::Reactivate)
                    {
                        communities.push_back(communityType);
                    }
                }
            }
        }

        return communities;
    }

    inline Core::Vector<Red::Handle<Red::questSpawner_NodeType>> FindSpawners()
    {
        Core::Vector<Red::Handle<Red::questSpawner_NodeType>> communities;

        for (const auto& spawnNode : GetNodesOfType<Red::questSpawnManagerNodeDefinition>())
        {
            for (const auto& spawnAction : spawnNode->actions)
            {
                if (const auto& spawnerType = Red::Cast<Red::questSpawner_NodeType>(spawnAction.type))
                {
                    if (spawnerType->action == Red::populationSpawnerObjectCtrlAction::Activate ||
                        spawnerType->action == Red::populationSpawnerObjectCtrlAction::Reactivate)
                    {
                        communities.push_back(spawnerType);
                    }
                }
            }
        }

        return communities;
    }

    inline Core::Vector<Red::Handle<Red::questSetVar_NodeType>> FindFactChanges()
    {
        Core::Vector<Red::Handle<Red::questSetVar_NodeType>> changes;

        for (const auto& factNode : GetNodesOfType<Red::questFactsDBManagerNodeDefinition>())
        {
            if (const auto& setVarType = Red::Cast<Red::questSetVar_NodeType>(factNode->type))
            {
                changes.push_back(setVarType);
            }
        }

        return changes;
    }

    inline Core::Vector<Red::Handle<Red::questEventManagerNodeDefinition>> FindAreaLinks()
    {
        return GetNodesOfType<Red::questEventManagerNodeDefinition>();
    }

    inline Core::Vector<Red::Handle<Red::questJournalNodeDefinition>> FindJournalEntries()
    {
        return GetNodesOfType<Red::questJournalNodeDefinition>();
    }

    inline Red::Handle<Red::questInputNodeDefinition> FindInputNode()
    {
        for (const auto& inputNode : GetNodesOfType<Red::questInputNodeDefinition>())
        {
            return inputNode;
        }

        return {};
    }

private:
    inline void CollectNodes(const Red::Handle<Red::questGraphDefinition>& aPhaseGraph)
    {
        for (const auto& node : aPhaseGraph->nodes)
        {
            m_nodesByType[node->GetNativeType()->GetName()].push_back(node);

            if (const auto& phaseNode = Red::Cast<Red::questPhaseNodeDefinition>(node))
            {
                if (phaseNode->phaseGraph)
                {
                    CollectNodes(phaseNode->phaseGraph);
                }
            }
        }
    }

    Core::Map<Red::CName, Core::Vector<Red::Handle<Red::graphGraphNodeDefinition>>> m_nodesByType;
};
}
