#pragma once

#include "Red/Addresses.hpp"

namespace Raw::EntityID
{
constexpr auto ToStringDEBUG = Core::RawFunc<
    /* addr = */ 0x140E75FC4 - Red::Addresses::ImageBase, // FIXME
    /* type = */ Red::CString* (*)(const Red::EntityID& aEntityID, Red::CString&)>();
}
