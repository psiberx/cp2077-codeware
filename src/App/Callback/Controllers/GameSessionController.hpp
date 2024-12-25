#pragma once

#include "App/Callback/CallbackSystem.hpp"
#include "App/Callback/CallbackSystemController.hpp"
#include "App/Callback/Events/GameSessionEvent.hpp"

namespace App
{
class GameSessionController : public CallbackSystemController
{
public:
    Core::Map<Red::CName, Red::CName> GetEvents() override
    {
        return {
            {CallbackSystem::SessionBeforeStartEventName, Red::GetTypeName<GameSessionEvent>()},
            {CallbackSystem::SessionBeforeEndEventName, Red::GetTypeName<GameSessionEvent>()},
            {CallbackSystem::SessionEndEventName, Red::GetTypeName<GameSessionEvent>()},
            {CallbackSystem::SessionBeforeSaveEventName, Red::GetTypeName<GameSessionEvent>()},
            {CallbackSystem::SessionAfterSaveEventName, Red::GetTypeName<GameSessionEvent>()},
            {CallbackSystem::SessionReadyEventName, Red::GetTypeName<GameSessionEvent>()},
            {CallbackSystem::SessionStartEventName, Red::GetTypeName<GameSessionEvent>()},
            {CallbackSystem::SessionPauseEventName, Red::GetTypeName<GameSessionEvent>()},
            {CallbackSystem::SessionResumeEventName, Red::GetTypeName<GameSessionEvent>()},
        };
    }

protected:
    bool OnActivateHook() override
    {
        return true;
    }

    bool OnDeactivateHook() override
    {
        return true;
    }
};
}
