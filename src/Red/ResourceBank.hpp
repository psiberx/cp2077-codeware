#pragma once

namespace Raw::ResourceBank
{
#if defined(__APPLE__)
// Mac ABI (R19): the bank value (ResourceLoader+0x48) in x0, the path in x1, the removed resource's Handle through x8.
constexpr auto ForgetResource = Core::RawFunc<
    /* addr = */ Red::AddressLib::ResourceBank_ForgetResource,
    /* type = */ Red::Handle<Red::CResource> (*)(uintptr_t aBank, const Red::ResourcePath aPath)>{};
#else
constexpr auto ForgetResource = Core::RawFunc<
    /* addr = */ Red::AddressLib::ResourceBank_ForgetResource,
    /* type = */ uintptr_t (*)(uintptr_t aBank, Red::Handle<Red::CResource>& aResource,
                               const Red::ResourcePath aPath)>{};
#endif
}
