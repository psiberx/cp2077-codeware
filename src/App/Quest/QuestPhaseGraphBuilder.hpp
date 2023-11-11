#pragma once

#include "Red/QuestsSystem.hpp"

namespace App
{
class QuestPhaseGraphBuilder
{
public:
    QuestPhaseGraphBuilder(Red::Handle<Red::questGraphDefinition>& aPhaseGraph,
                                    Red::QuestNodeID aNextNodeID = 10001)
        : m_graph(aPhaseGraph)
        , m_nextNodeID(aNextNodeID)
    {
    }

    Red::Handle<Red::questSocketDefinition> ResolveSocket(Red::Handle<Red::questNodeDefinition>& aNode,
                                                          Red::questSocketType aSocketType,
                                                          Red::CName aSocketName)
    {
        for (const auto& graphSocket : aNode->sockets)
        {
            if (const auto& questSocket = Red::Cast<Red::questSocketDefinition>(graphSocket))
            {
                if (questSocket->type == aSocketType && questSocket->name == aSocketName)
                {
                    return questSocket;
                }
            }
        }

        auto questSocket = Red::MakeHandle<Red::questSocketDefinition>();
        questSocket->type = aSocketType;
        questSocket->name = aSocketName;

        aNode->sockets.PushBack(questSocket);

        Raw::QuestSocketDefinition::OwnerNode::Ref(questSocket.instance) = aNode;

        return questSocket;
    }

    void AddConnection(Red::Handle<Red::questNodeDefinition>& aOut, Red::Handle<Red::questNodeDefinition>& aIn)
    {
        auto outSocket = ResolveSocket(aOut, Red::questSocketType::Output, "Out");
        auto inSocket = ResolveSocket(aIn, Red::questSocketType::Input, "In");

        auto connection = Red::MakeHandle<Red::graphGraphConnectionDefinition>();
        connection->source = outSocket;
        connection->destination = inSocket;

        outSocket->connections.PushBack(connection);
        inSocket->connections.PushBack(connection);
    }

    Red::Handle<Red::questPauseConditionNodeDefinition> AddDynamicEntitySpawnWaitNode(Red::NodeRef aReference = {})
    {
        auto comparisonParam = Red::MakeHandle<Red::questComparisonParam>();
        comparisonParam->comparisonType = Red::EComparisonType::GreaterOrEqual;
        comparisonParam->count = 1;
        comparisonParam->entireCommunity = false;

        auto conditionType = Red::MakeHandle<Red::questCharacterSpawned_ConditionType>();
        conditionType->comparisonParams = comparisonParam;
        conditionType->objectRef.type = Red::gameEntityReferenceType::EntityRef;
        conditionType->objectRef.reference = aReference;

        auto condition = Red::MakeHandle<Red::questCharacterCondition>();
        condition->type = conditionType;

        auto pauseNode = Red::MakeHandle<Red::questPauseConditionNodeDefinition>();
        pauseNode->id = m_nextNodeID++;
        pauseNode->condition = condition;

        m_graph->nodes.PushBack(pauseNode);

        Raw::QuestConditionType::OwnerNodeID::Ref(conditionType.instance) = pauseNode->id;

        return pauseNode;
    }

    Red::Handle<Red::questPauseConditionNodeDefinition> AddStaticEntitySpawnWait(Red::NodeRef aReference = {})
    {
        auto condition = Red::MakeHandle<Red::questNodeLoadingCondition>();
        condition->objectRef = aReference;
        condition->inverted = false;

        auto pauseNode = Red::MakeHandle<Red::questPauseConditionNodeDefinition>();
        pauseNode->id = m_nextNodeID++;
        pauseNode->condition = condition;

        m_graph->nodes.PushBack(pauseNode);

        return pauseNode;
    }

    Red::Handle<Red::questEventManagerNodeDefinition> AddEventDispatch(Red::NodeRef aTarget = {})
    {
        auto eventNode = Red::MakeHandle<Red::questEventManagerNodeDefinition>();
        eventNode->id = m_nextNodeID++;
        eventNode->isUiEvent = false;
        eventNode->isObjectPlayer = false;
        eventNode->objectRef.type = Red::gameEntityReferenceType::EntityRef;
        eventNode->objectRef.reference = aTarget;

        m_graph->nodes.PushBack(eventNode);

        return eventNode;
    }

    Red::Handle<Red::questEventManagerNodeDefinition> AddSendEventNode(Red::NodeRef aTarget,
                                                                       Red::Handle<Red::Event>& aEvent)
    {
        auto eventNode = AddEventDispatch(aTarget);
        eventNode->event = std::move(aEvent);

        return eventNode;
    }

private:
    Red::Handle<Red::questGraphDefinition>& m_graph;
    Red::QuestNodeID m_nextNodeID;
};
}
