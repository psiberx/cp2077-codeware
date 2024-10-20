#pragma once

#include "App/Quest/QuestPhaseRegistry.hpp"
#include "Red/QuestsSystem.hpp"

namespace App
{
class QuestPhaseExecutor
{
public:
    QuestPhaseExecutor(Core::SharedPtr<App::QuestPhaseRegistry> aQuestPhaseRegistry,
                       Red::questIQuestsSystem* aQuestsSystem)
        : m_questPhaseRegistry(std::move(aQuestPhaseRegistry))
        , m_questsSystem(aQuestsSystem)
        , m_questsSystemMutex(Raw::QuestsSystem::Mutex::Ref(aQuestsSystem))
        , m_rootPhaseInstance(Raw::QuestsSystem::RootPhase::Ref(aQuestsSystem))
    {
    }

    inline void ExecuteNode(const Red::Handle<Red::questNodeDefinition>& aNode,
                            Red::questPhaseInstance* aPhaseInstance = nullptr)
    {
        std::unique_lock _(m_questsSystemMutex);

        if (!aPhaseInstance)
        {
            aPhaseInstance = m_rootPhaseInstance;
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
        std::unique_lock _(m_questsSystemMutex);

        if (!aPhaseInstance)
        {
            aPhaseInstance = m_rootPhaseInstance;
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

    inline void ExecutePath(const Red::QuestNodePath& aPhaseNodePath, Red::QuestNodeID aInputNodeID,
                            Red::CName aInputSocketName)
    {
        std::unique_lock _(m_questsSystemMutex);

        Red::QuestContext context{};
        Raw::QuestsSystem::CreateContext(m_questsSystem, &context, 1, 0, -1, -1);

        Red::DynArray<Red::QuestNodeSocket> outputSockets;
        auto res = Raw::QuestPhaseInstance::ExecutePath(m_rootPhaseInstance, context, aPhaseNodePath, aInputNodeID,
                                             aInputSocketName, outputSockets);
    }

    // inline void ExecuteGraph(const Red::Handle<Red::questNodeDefinition>& aInputNode,
    //                          const Red::QuestNodeSocket& aInputSocket,
    //                          const Red::QuestNodePath& aPhaseNodePath)
    // {
    //     std::unique_lock _(m_questsSystemMutex);
    //
    //     Red::QuestContext context{};
    //     Raw::QuestsSystem::CreateContext(m_questsSystem, &context, 1, 0, -1, -1);
    //
    //     {
    //         auto parentPhaseNodePath = aPhaseNodePath;
    //         auto maxParentNodeDepth = parentPhaseNodePath.size - 1;
    //         for (auto depth = 1; depth <= maxParentNodeDepth; ++depth)
    //         {
    //             parentPhaseNodePath.size = depth;
    //             context.phaseStack.PushBack(m_questPhaseRegistry->GetPhaseInstance(parentPhaseNodePath));
    //         }
    //     }
    //
    //     auto phaseInstance = m_questPhaseRegistry->GetPhaseInstance(aPhaseNodePath);
    //
    //     Red::DynArray<Red::QuestNodeSocket> outputSockets;
    //     Raw::QuestPhaseInstance::ExecuteGraph(phaseInstance, context, aInputNode, aInputSocket, true, outputSockets);
    // }

    // inline void ExecuteGraph(const Red::Handle<Red::questNodeDefinition>& aInputNode,
    //                          const Red::QuestNodeSocket& aInputSocket,
    //                          Red::questPhaseInstance* aPhaseInstance)
    // {
    //     std::unique_lock _(m_questsSystemMutex);
    //
    //     Red::QuestContext context{};
    //     Raw::QuestsSystem::CreateContext(m_questsSystem, &context, 1, 0, -1, -1);
    //
    //     Red::DynArray<Red::QuestNodeSocket> outputSockets;
    //     Raw::QuestPhaseInstance::ExecuteGraph(aPhaseInstance, context, aInputNode, aInputSocket, true, outputSockets);
    // }

private:
    Core::SharedPtr<QuestPhaseRegistry> m_questPhaseRegistry;
    Red::questIQuestsSystem* m_questsSystem;
    Red::SharedSpinLock& m_questsSystemMutex;
    Red::Handle<Red::questPhaseInstance>& m_rootPhaseInstance;
};
}
