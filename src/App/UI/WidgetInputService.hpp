#pragma once

#include "Core/Foundation/Feature.hpp"
#include "Core/Hooking/HookingAgent.hpp"
#include "Core/Logging/LoggingAgent.hpp"
#include "Red/InkSystem.hpp"

namespace App
{
class WidgetInputService
    : public Core::Feature
    , public Core::HookingAgent
    , public Core::LoggingAgent
{
protected:
    void OnBootstrap() override;
    void OnShutdown() override;

    static void OnCharacterInput(Red::InkSystem* aSystem, Red::EInputKey aKey, Red::EInputAction aAction);
    static std::string ToCharacter(Red::EInputKey aKey);
    static bool IsCharacterInput(Red::EInputKey aKey);
};
}
