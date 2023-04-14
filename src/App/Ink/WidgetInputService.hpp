#pragma once

#include "Core/Foundation/Feature.hpp"
#include "Core/Hooking/HookingAgent.hpp"
#include "Core/Logging/LoggingAgent.hpp"
#include "Red/InkCore.hpp"
#include "Red/InkSystem.hpp"

namespace App
{
using RawInputCallback = void(*)(Red::KeyboardState& aState, Red::EInputAction aAction, Red::EInputKey aKey);

class WidgetInputService
    : public Core::Feature
    , public Core::HookingAgent
    , public Core::LoggingAgent
{
public:
    void SetCallback(RawInputCallback aCallback);
    void ClearCallback();

protected:
    void OnBootstrap() override;
    void OnShutdown() override;

    static void OnInput(Red::InkSystem* aSystem, Red::EInputKey aKey, Red::EInputAction aAction);
    static std::string ToCharacter(Red::EInputKey aKey);
    static bool IsCharacter(Red::EInputKey aKey);
};
}
