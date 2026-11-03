#pragma once

#include "Core/Foundation/Feature.hpp"
#include "Support/RED4ext/V1Compat.hpp"
#include "Core/Hooking/HookingDriver.hpp"
#include "Core/Logging/LoggingDriver.hpp"
#include "Core/Memory/AddressResolver.hpp"

namespace Support
{
class RED4extProvider
    : public Core::Feature
    , public Core::LoggingDriver
    , public Core::HookingDriver
    , public Core::AddressResolver
{
public:
    RED4extProvider(RED4ext::v1::PluginHandle aPlugin, const RED4ext::v1::Sdk* aSdk) noexcept;

    void LogInfo(const std::string_view& aMessage) override;
    void LogWarning(const std::string_view& aMessage) override;
    void LogError(const std::string_view& aMessage) override;
    void LogDebug(const std::string_view& aMessage) override;
    void LogFlush() override;

    bool HookAttach(uintptr_t aAddress, void* aCallback) override;
    bool HookAttach(uintptr_t aAddress, void* aCallback, void** aOriginal) override;
    bool HookDetach(uintptr_t aAddress) override;

    uintptr_t ResolveAddress(uint32_t aAddressID) override;

    auto EnableLogging() noexcept
    {
        m_enableLogging = true;
        return Defer(this);
    }

    auto EnableHooking() noexcept
    {
        m_enableHooking = true;
        return Defer(this);
    }

    auto EnableAddressLibrary() noexcept
    {
        m_enableAddressLibrary = true;
        return Defer(this);
    }

    auto RegisterScripts(const std::filesystem::path& aPath) noexcept
    {
#if defined(__APPLE__)
        // macOS: the redscript compiler runs offline (tools/build-cache.py builds the script cache), so there is
        // nothing to add at run time.
        (void)aPath;
#else
        m_sdk->scripts->Add(m_plugin, aPath.c_str());
#endif
        return Defer(this);
    }

protected:
    void OnInitialize() override;

    RED4ext::v1::PluginHandle m_plugin;
    const RED4ext::v1::Sdk* m_sdk;
    bool m_enableLogging;
    bool m_enableHooking;
    bool m_enableAddressLibrary;
};
}
