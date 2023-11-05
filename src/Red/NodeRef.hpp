#pragma once

#include "Addresses.hpp"
#include "Red/Strings.hpp"

namespace Raw::NodeRef
{
constexpr auto Create = Core::RawFunc<
    /* addr = */ Red::Addresses::NodeRef_Create,
    /* type = */ Red::NodeRef* (*)(Red::NodeRef& aOut, Red::StringView& aReference)>();
}
