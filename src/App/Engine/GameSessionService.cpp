#include "GameSessionService.hpp"

void App::GameSessionService::OnBootstrap()
{
    Hook<Raw::GetScriptGameInstance>(&GetScriptGameInstance);
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
