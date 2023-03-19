#pragma once

#include "Core/Foundation/Feature.hpp"
#include "Core/Hooking/HookingAgent.hpp"
#include "Red/Scripting.hpp"

namespace App
{
class ScriptingService
    : public Core::Feature
    , public Core::HookingAgent
{
protected:
    void OnBootstrap() override;

    static void OnInitializeScriptable(Red::IScriptable* aInstance, Red::CClass* aClass, void* aValueHolder);
};
}
