#pragma once

#include "Red/Strings.hpp"

namespace Raw::ResourcePath
{
constexpr auto Create = Core::RawFunc<
    /* addr = */ Red::AddressLib::ResourcePath_Create,
    /* type = */ Red::ResourcePath* (*)(Red::ResourcePath* aOut, Red::StringView* aPathStr)>();
}
