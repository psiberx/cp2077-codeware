#pragma once

// R13. Core::HookingDriver for macOS. A thin layer over RED4ext's hooking interface, the same call the
// GameInstance hook in MacSupport.cpp makes. RED4ext installs the hook as "manual inline" or "gum classic"
// and only for offsets on the RED4EXT_GUM_HOOK_OFFSETS allowlist.

#include <cstdint>
#include <cstdio>

#include "Core/Hooking/HookingDriver.hpp"
#include "MacDiag.hpp"
#include "MacHookChain.hpp"
#include "MacTrap.hpp"

#include <RED4ext/Api/v1/Sdk.hpp>

namespace Red
{
uintptr_t MacGameBase();
}

namespace Support
{
class MacHookingDriver : public Core::HookingDriver
{
public:
    MacHookingDriver(RED4ext::v1::PluginHandle aPlugin, const RED4ext::v1::Sdk* aSdk) noexcept
        : m_plugin(aPlugin)
        , m_sdk(aSdk)
    {
    }

    bool HookAttach(uintptr_t aAddress, void* aCallback) override
    {
        return Attach(aAddress, aCallback, nullptr);
    }

    bool HookAttach(uintptr_t aAddress, void* aCallback, void** aOriginal) override
    {
        return Attach(aAddress, aCallback, aOriginal);
    }

    bool HookDetach(uintptr_t aAddress) override
    {
        if (!m_sdk || !m_sdk->hooking || !m_sdk->hooking->Detach)
        {
            std::fprintf(stderr, "[cw] hook detach: no hooking interface\n");
            return false;
        }
        const bool ok = m_sdk->hooking->Detach(m_plugin, reinterpret_cast<void*>(aAddress));
        MAC_DIAG("[cw] hook detach rva=0x%lx ok=%d\n", static_cast<unsigned long>(aAddress - Red::MacGameBase()), ok ? 1 : 0);
        return ok;
    }

private:
    static bool RealAttach(uintptr_t aTarget, void* aDetour, void** aOriginal, void* aContext)
    {
        auto* self = static_cast<MacHookingDriver*>(aContext);
        return self->m_sdk->hooking->Attach(self->m_plugin, reinterpret_cast<void*>(aTarget), aDetour, aOriginal);
    }

    bool Attach(uintptr_t aAddress, void* aCallback, void** aOriginal)
    {
        if (!m_sdk || !m_sdk->hooking || !m_sdk->hooking->Attach)
        {
            std::fprintf(stderr, "[cw] hook attach: no hooking interface\n");
            return false;
        }
        if (Mac::IsTrapAddress(aAddress))
        {
            // R17. The target resolved to a trap stub: the function has no Mac address yet, so there is nothing to hook.
            std::fprintf(stderr, "[cw] hook refused: target is a trap stub (not on Mac yet), detour=%p\n", aCallback);
            return false;
        }
        if (aAddress == 0 || !aCallback)
        {
            std::fprintf(stderr, "[cw] hook attach: null target or detour (target=%p)\n", reinterpret_cast<void*>(aAddress));
            return false;
        }
        // R22. Through the hook chain: the target may also be hooked by the ArchiveXL plugin (RED4ext allows one hook per target).
        const bool ok = Mac::HookChain::Attach(aAddress, aCallback, aOriginal, &RealAttach, this);
        MAC_DIAG_UNLESS(ok, "[cw] hook attach target=%p rva=0x%lx detour=%p original=%p ok=%d\n",
                        reinterpret_cast<void*>(aAddress), static_cast<unsigned long>(aAddress - Red::MacGameBase()),
                        aCallback, aOriginal ? reinterpret_cast<void*>(*aOriginal) : nullptr, ok ? 1 : 0);
        return ok;
    }

    RED4ext::v1::PluginHandle m_plugin;
    const RED4ext::v1::Sdk* m_sdk;
};
}
