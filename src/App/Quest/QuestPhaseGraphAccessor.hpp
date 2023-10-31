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

    inline Red::Handle<Red::questInputNodeDefinition> FindInputNode()
    {
        for (const auto& inputNode : GetNodesOfType<Red::questInputNodeDefinition>())
        {
            return inputNode;
        }

        return {};
    }

    inline Red::Handle<Red::questJournalEntry_NodeType> FindPointOfInterestMappin()
    {
        for (const auto& node : GetNodesOfType<Red::questJournalNodeDefinition>())
        {
            if (const auto& nodeType = Red::Cast<Red::questJournalEntry_NodeType>(node->type))
            {
                if (nodeType->path->className == Red::GetTypeName<Red::gameJournalPointOfInterestMappin>())
                {
                    return nodeType;
                }
            }
        }

        return {};
    }

    inline Red::Handle<Red::questJournalChangeMappinPhase_NodeType> FindCompletedPointOfInterestMappin()
    {
        for (const auto& node : GetNodesOfType<Red::questJournalNodeDefinition>())
        {
            if (const auto& nodeType = Red::Cast<Red::questJournalChangeMappinPhase_NodeType>(node->type))
            {
                if (nodeType->path->className == Red::GetTypeName<Red::gameJournalPointOfInterestMappin>() &&
                    nodeType->phase == Red::gamedataMappinPhase::CompletedPhase)
                {
                    return nodeType;
                }
            }
        }

        return {};
    }

    inline Red::Handle<Red::questCharacterKilled_ConditionType> FindCharacterKill()
    {
        for (const auto& node : GetNodesOfType<Red::questPauseConditionNodeDefinition>())
        {
            if (const auto& condition = Red::Cast<Red::questCharacterCondition>(node->condition))
            {
                if (const auto& conditionType = Red::Cast<Red::questCharacterKilled_ConditionType>(condition->type))
                {
                    return conditionType;
                }
            }
        }

        for (const auto& node : GetNodesOfType<Red::questConditionNodeDefinition>())
        {
            if (const auto& condition = Red::Cast<Red::questCharacterCondition>(node->condition))
            {
                if (const auto& conditionType = Red::Cast<Red::questCharacterKilled_ConditionType>(condition->type))
                {
                    return conditionType;
                }
            }
        }

        return {};
    }

    inline Core::Vector<Red::Handle<Red::questCommunityTemplate_NodeType>> FindCommunities()
    {
        Core::Vector<Red::Handle<Red::questCommunityTemplate_NodeType>> communities;

        for (const auto& node : GetNodesOfType<Red::questSpawnManagerNodeDefinition>())
        {
            for (const auto& action : node->actions)
            {
                if (const auto& nodeType = Red::Cast<Red::questCommunityTemplate_NodeType>(action.type))
                {
                    if (nodeType->action == Red::populationSpawnerObjectCtrlAction::Activate ||
                        nodeType->action == Red::populationSpawnerObjectCtrlAction::Reactivate)
                    {
                        communities.push_back(nodeType);
                    }
                }
            }
        }

        return communities;
    }

    inline Core::Vector<Red::Handle<Red::questSpawner_NodeType>> FindSpawners()
    {
        Core::Vector<Red::Handle<Red::questSpawner_NodeType>> communities;

        for (const auto& node : GetNodesOfType<Red::questSpawnManagerNodeDefinition>())
        {
            for (const auto& action : node->actions)
            {
                if (const auto& nodeType = Red::Cast<Red::questSpawner_NodeType>(action.type))
                {
                    if (nodeType->action == Red::populationSpawnerObjectCtrlAction::Activate ||
                        nodeType->action == Red::populationSpawnerObjectCtrlAction::Reactivate)
                    {
                        communities.push_back(nodeType);
                    }
                }
            }
        }

        return communities;
    }

    inline Core::Vector<Red::Handle<Red::questSetVar_NodeType>> FindFactChanges()
    {
        Core::Vector<Red::Handle<Red::questSetVar_NodeType>> changes;

        for (const auto& node : GetNodesOfType<Red::questFactsDBManagerNodeDefinition>())
        {
            if (const auto& setVarType = Red::Cast<Red::questSetVar_NodeType>(node->type))
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

    inline Core::Vector<Red::Handle<Red::questJournalEntry_ConditionType>> FindJournalObjectives()
    {
        Core::Vector<Red::Handle<Red::questJournalEntry_ConditionType>> objectives;

        for (const auto& node : GetNodesOfType<Red::questPauseConditionNodeDefinition>())
        {
            if (const auto& condition = Red::Cast<Red::questJournalCondition>(node->condition))
            {
                if (const auto& conditionType = Red::Cast<Red::questJournalEntry_ConditionType>(condition->type))
                {
                    if (conditionType->state == Red::gameJournalEntryUserState::Active)
                    {
                        objectives.push_back(conditionType);
                    }
                }
            }
        }

        return objectives;
    }

    inline Core::Vector<Red::Handle<Red::questInventory_ConditionType>> FindLootObjectives()
    {
        Core::Vector<Red::Handle<Red::questInventory_ConditionType>> objectives;

        for (const auto& node : GetNodesOfType<Red::questPauseConditionNodeDefinition>())
        {
            if (const auto& condition = Red::Cast<Red::questObjectCondition>(node->condition))
            {
                if (const auto& conditionType = Red::Cast<Red::questInventory_ConditionType>(condition->type))
                {
                    if (conditionType->isPlayer)
                    {
                        objectives.push_back(conditionType);
                    }
                }
            }
        }

        return objectives;
    }

    inline Red::Handle<Red::questInteraction_ConditionType> FindLootContainer()
    {
        for (const auto& node : GetNodesOfType<Red::questPauseConditionNodeDefinition>())
        {
            if (const auto& condition = Red::Cast<Red::questObjectCondition>(node->condition))
            {
                if (const auto& conditionType = Red::Cast<Red::questInteraction_ConditionType>(condition->type))
                {
                    if (conditionType->eventType == Red::questObjectInteractionEventType::Executed)
                    {
                        return conditionType;
                    }
                }
            }
        }

        return {};
    }

private:
    inline void CollectNodes(const Red::Handle<Red::questGraphDefinition>& aPhaseGraph)
    {
        Core::Vector<Red::Handle<Red::questPhaseNodeDefinition>> nestedPhases;

        for (const auto& node : aPhaseGraph->nodes)
        {
            m_nodesByType[node->GetType()->name].push_back(node);

            if (const auto& phaseNode = Red::Cast<Red::questPhaseNodeDefinition>(node))
            {
                if (phaseNode->phaseGraph)
                {
                    nestedPhases.push_back(phaseNode);
                }
            }
        }

        for (const auto& phaseNode : nestedPhases)
        {
            CollectNodes(phaseNode->phaseGraph);
        }
    }

    Core::Map<Red::CName, Core::Vector<Red::Handle<Red::graphGraphNodeDefinition>>> m_nodesByType;
};
}
