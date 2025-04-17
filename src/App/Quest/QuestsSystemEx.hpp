#pragma once

#include "Red/QuestsSystem.hpp"

namespace App
{
struct QuestsSystemEx : Red::questQuestsSystem
{
    void ExecuteNode(const Red::Handle<Red::questNodeDefinition>& aNode, Red::Optional<Red::CName> aInputSocket)
    {
        std::unique_lock _(Raw::QuestsSystem::Mutex::Ref(this));

        auto& rootPhaseInstance = Raw::QuestsSystem::RootPhase::Ref(this);

        Red::QuestContext context{};
        Raw::QuestsSystem::CreateContext(this, &context, 1, 0, -1, -1);

        context.phaseStack.PushBack(rootPhaseInstance);

        Red::QuestNodeSocket inputSocket{aInputSocket.value};
        Red::DynArray<Red::QuestNodeSocket> outputSockets;

        Raw::QuestPhaseInstance::ExecuteNode(rootPhaseInstance, aNode, context, inputSocket, outputSockets);

        context.phaseStack.Clear();
    }
};
}

RTTI_EXPAND_CLASS(Red::questQuestsSystem, App::QuestsSystemEx, {
    RTTI_METHOD(ExecuteNode);
});
