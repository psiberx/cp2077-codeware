#pragma once

#include "Addresses.hpp"

namespace Raw::NodeRef
{
constexpr auto Create = Core::RawFunc<
    /* addr = */ Red::Addresses::NodeRef_Create,
    /* type = */ Red::NodeRef* (*)(Red::NodeRef& aOut, std::string_view& aReference)>();
}
