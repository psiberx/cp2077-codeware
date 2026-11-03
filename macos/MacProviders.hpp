#pragma once

// R17 B3. The macOS platform feature of App::Application. It plays the role of Support::MinHookProvider and
// Support::RED4extProvider on Windows: it sets the three Core defaults the shared sources use.
//   Core::AddressResolver  Support::MacAddressResolver (Mac rows, then the SDK table, then the trap stubs)
//   Core::HookingDriver    Support::MacHookingDriver (RED4ext hooking interface, refuses trap stubs)
//   Core::LoggingDriver    stderr, lines start with "[cw]"; the launcher captures stderr
// Defaults are set in OnInitialize, which runs when the Register<> chain ends, i.e. while the Application is built.

#include "MacAddressResolver.hpp"
#include "MacHookingDriver.hpp"

#include "Core/Foundation/Feature.hpp"
#include "Core/Logging/LoggingDriver.hpp"
#include "Core/Memory/AddressResolver.hpp"

#include <cstdio>
#include <string_view>

namespace Support
{
class MacPlatformProvider
    : public Core::Feature
    , public Core::LoggingDriver
{
public:
    MacPlatformProvider(RED4ext::v1::PluginHandle aPlugin, const RED4ext::v1::Sdk* aSdk) noexcept
        : m_driver(aPlugin, aSdk)
    {
    }

    void LogInfo(const std::string_view& aMessage) override
    {
        Print("", aMessage);
    }

    void LogWarning(const std::string_view& aMessage) override
    {
        Print("WARN ", aMessage);
    }

    void LogError(const std::string_view& aMessage) override
    {
        Print("ERROR ", aMessage);
    }

    void LogDebug(const std::string_view& aMessage) override
    {
        Print("DEBUG ", aMessage);
    }

    void LogFlush() override
    {
        std::fflush(stderr);
    }

protected:
    void OnInitialize() override
    {
        Core::AddressResolver::SetDefault(m_resolver);
        Core::HookingDriver::SetDefault(m_driver);
        Core::LoggingDriver::SetDefault(*this);
    }

private:
    static void Print(const char* aLevel, const std::string_view& aMessage)
    {
        std::fprintf(stderr, "[cw] %s%.*s\n", aLevel, static_cast<int>(aMessage.size()), aMessage.data());
    }

    MacAddressResolver m_resolver;
    MacHookingDriver m_driver;
};
}
