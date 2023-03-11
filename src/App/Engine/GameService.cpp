#include "GameService.hpp"

void App::GameService::OnBootstrap()
{
    Hook<Raw::GetScriptGameInstance>(&GetScriptGameInstance);
}

void App::GameService::GetScriptGameInstance(Red::IScriptable* aContext, Red::CStackFrame* aFrame,
                                             Red::ScriptGameInstance* aRet, Red::CBaseRTTIType* aType)
{
    static const Red::ScriptGameInstance game{};

    aFrame->code++;

    if (aRet)
    {
        *aRet = game;
    }
}
