#include "GameSessionService.hpp"

void App::GameSessionService::OnBootstrap()
{
    if (!Hook<Raw::GetScriptGameInstance>(&GetScriptGameInstance))
        throw std::runtime_error("Failed to hook ScriptGameInstance.");
}

void App::GameSessionService::GetScriptGameInstance(Red::IScriptable* aContext, Red::CStackFrame* aFrame,
                                                    Red::ScriptGameInstance* aRet, Red::CBaseRTTIType* aType)
{
    static const Red::ScriptGameInstance game{};

    aFrame->code++;

    if (aRet)
    {
        *aRet = game;
    }
}
