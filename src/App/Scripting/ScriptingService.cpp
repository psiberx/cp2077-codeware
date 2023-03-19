#include "ScriptingService.hpp"

void App::ScriptingService::OnBootstrap()
{
    if (!HookAfter<Raw::IScriptable::InitializeScriptData>(&OnInitializeScriptable))
        throw std::runtime_error("Failed to hook IScriptable::InitializeScriptData.");
}

void App::ScriptingService::OnInitializeScriptable(Red::IScriptable* aInstance, Red::CClass* aClass, void*)
{
    if (aClass->flags.isScriptedClass)
    {
        Red::CallVirtual(aInstance, aClass, "OnConstruct");
    }
}
