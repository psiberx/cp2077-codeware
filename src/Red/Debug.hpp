#pragma once

namespace Raw::EntityID
{
constexpr auto ToStringDEBUG = Core::RawFunc<
    /* addr = */ 0x140E75FC4 - Red::Address::ImageBase, // FIXME
    /* type = */ Red::CString* (*)(const Red::EntityID& aEntityID, Red::CString&)>();
}
