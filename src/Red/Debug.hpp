#pragma once

namespace Raw::EntityID
{
constexpr auto ToStringDEBUG = Core::RawFunc<
    /* addr = */ 0x0E75FC4, // FIXME
    /* type = */ Red::CString* (*)(const Red::EntityID& aEntityID, Red::CString&)>();
}
