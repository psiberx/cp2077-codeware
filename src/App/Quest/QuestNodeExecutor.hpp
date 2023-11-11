#pragma once

#include "App/Quest/QuestPhaseRegistry.hpp"
#include "Red/QuestsSystem.hpp"

namespace App
{
class QuestNodeExecutor
{
public:
    QuestNodeExecutor(Core::SharedPtr<App::QuestPhaseRegistry> aQuestPhaseRegistry,
                      RED4ext::questIQuestsSystem* aQuestsSystem)
        : m_questPhaseRegistry(std::move(aQuestPhaseRegistry))
        , m_questsSystem(aQuestsSystem)
    {
    }

    inline void ExecuteNode(const Red::Handle<Red::questNodeDefinition>& aNode,
                            Red::questPhaseInstance* aPhaseInstance = nullptr)
    {
        if (!aPhaseInstance)
        {
            Red::QuestNodePath rootPhasePath;
            rootPhasePath.PushBack(0);
            aPhaseInstance = m_questPhaseRegistry->GetPhaseInstance({rootPhasePath});
        }

        Red::QuestContext context{};
        Raw::QuestsSystem::CreateContext(m_questsSystem, &context, 1, 0, -1, -1);

        context.phaseStack.PushBack(aPhaseInstance);

        Red::QuestNodeSocket inputSocket;
        Red::DynArray<Red::QuestNodeSocket> outputSockets;

        Raw::QuestPhaseInstance::ExecuteNode(aPhaseInstance, aNode, context, inputSocket, outputSockets);

        context.phaseStack.Clear();
    }

    inline void ExecuteNodes(const Core::Vector<Red::Handle<Red::questNodeDefinition>>& aNodes,
                             Red::questPhaseInstance* aPhaseInstance = nullptr)
    {
        if (!aPhaseInstance)
        {
            Red::QuestNodePath rootPhasePath;
            rootPhasePath.PushBack(0);
            aPhaseInstance = m_questPhaseRegistry->GetPhaseInstance({rootPhasePath});
        }

        Red::QuestContext context{};
        Raw::QuestsSystem::CreateContext(m_questsSystem, &context, 1, 0, -1, -1);

        context.phaseStack.PushBack(aPhaseInstance);

        Red::QuestNodeSocket inputSocket;
        Red::DynArray<Red::QuestNodeSocket> outputSockets;

        for (const auto& node : aNodes)
        {
            Raw::QuestPhaseInstance::ExecuteNode(aPhaseInstance, node, context, inputSocket, outputSockets);
        }

        context.phaseStack.Clear();
    }

    inline void ExecuteGraph(const Red::Handle<Red::questNodeDefinition>& aInputNode,
                             const Red::QuestNodeSocket& aInputSocket,
                             const Red::QuestNodePath& aPhaseNodePath)
    {
        Red::QuestContext context{};
        Raw::QuestsSystem::CreateContext(m_questsSystem, &context, 1, 0, -1, -1);

        {
            auto parentPhaseNodePath = aPhaseNodePath;
            auto maxParentNodeDepth = parentPhaseNodePath.size - 1;
            for (auto depth = 1; depth <= maxParentNodeDepth; ++depth)
            {
                parentPhaseNodePath.size = depth;
                context.phaseStack.PushBack(m_questPhaseRegistry->GetPhaseInstance(parentPhaseNodePath));
            }
        }

        auto phaseInstance = m_questPhaseRegistry->GetPhaseInstance(aPhaseNodePath);

        Red::DynArray<Red::QuestNodeSocket> outputSockets;
        Raw::QuestPhaseInstance::ExequteGraph(phaseInstance, context, aInputNode, aInputSocket, true, outputSockets);
    }

    inline void ExecuteGraph(const Red::Handle<Red::questNodeDefinition>& aInputNode,
                             const Red::QuestNodeSocket& aInputSocket,
                             Red::questPhaseInstance* aPhaseInstance)
    {
        Red::QuestContext context{};
        Raw::QuestsSystem::CreateContext(m_questsSystem, &context, 1, 0, -1, -1);

        Red::DynArray<Red::QuestNodeSocket> outputSockets;
        Raw::QuestPhaseInstance::ExequteGraph(aPhaseInstance, context, aInputNode, aInputSocket, true, outputSockets);
    }

private:
    Core::SharedPtr<QuestPhaseRegistry> m_questPhaseRegistry;
    Red::questIQuestsSystem* m_questsSystem;
};
}
