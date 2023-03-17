#pragma once

#include "Core/Foundation/Feature.hpp"
#include "Core/Hooking/HookingAgent.hpp"
#include "Red/GameInstance.hpp"

namespace App
{
class GameSessionService
    : public Core::Feature
    , public Core::HookingAgent
{
protected:
    void OnBootstrap() override;

    static void GetScriptGameInstance(Red::IScriptable* aContext, Red::CStackFrame* aFrame,
                                      Red::ScriptGameInstance* aRet, Red::CBaseRTTIType* aType);
};
}
