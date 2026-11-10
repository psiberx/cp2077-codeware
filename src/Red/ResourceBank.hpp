#pragma once

namespace Raw::ResourceBank
{
constexpr auto ForgetResource = Core::RawFunc<
    /* addr = */ Red::AddressLib::ResourceBank_ForgetResource,
    /* type = */ uintptr_t (*)(Red::ResourceBank* aBank, Red::Handle<Red::CResource>& aResource,
                               const Red::ResourcePath aPath)>{};
}
