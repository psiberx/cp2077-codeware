#pragma once

#include "Core/Foundation/Feature.hpp"
#include "Core/Hooking/HookingAgent.hpp"
#include "Core/Logging/LoggingAgent.hpp"
#include "Red/MappinSystem.hpp"

namespace App
{
class OpenWorldTracker
    : public Core::Feature
    , public Core::HookingAgent
    , public Core::LoggingAgent
{
protected:
    void OnBootstrap() override;
    static void OnSetPoiMappinPhase(void* aMappin, Red::gamedataMappinPhase aMappinPhase);
};
}
