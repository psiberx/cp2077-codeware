#pragma once

#include "Core/Foundation/Application.hpp"
#include "Core/Logging/LoggingAgent.hpp"

#if defined(__APPLE__)
#include "Support/RED4ext/V1Compat.hpp"
#endif

namespace App
{
class Application
    : public Core::Application,
      public Core::LoggingAgent
{
public:
#if defined(__APPLE__)
    // aModule is an address inside this dylib (Core::ModuleImage finds the plugin path from it with dladdr).
    Application(void* aModule, RED4ext::v1::PluginHandle aPlugin, const RED4ext::v1::Sdk* aSdk);
#else
    explicit Application(HMODULE aHandle, const RED4ext::v1::Sdk* aSdk = nullptr);
#endif

protected:
    void OnStarting() override;
    void OnStarted() override;
};
}
