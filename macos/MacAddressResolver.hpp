#pragma once

// R13. Address resolver for Codeware's Core::RawFunc / RawPtr ids on macOS.
// Without a default, Core::AddressResolver::GetDefault() asserts (the 4A boot 3 abort in InkSystem::Get).

#include <cstdint>

#include "Core/Memory/AddressResolver.hpp"

namespace Red
{
// Base address of the Cyberpunk2077 (MH_EXECUTE) image. Defined in MacSupport.cpp.
uintptr_t MacGameBase();
}

namespace Support
{
// Holds the Mac rows (id -> RVA) and falls back to the SDK resolver for every other id.
// An id that neither knows logs "[cw] unknown address id 0x..." once and returns 0. It never aborts.
class MacAddressResolver : public Core::AddressResolver
{
public:
    uintptr_t ResolveAddress(uint32_t aAddressID) override;
};
}
