#pragma once

namespace Raw::ResourcePath
{
#if defined(__APPLE__)
// Mac ABI (R19): the path is a StringView passed by value in two registers (data, size) and the 8 byte ResourcePath comes
// back in x0. No out pointer. The string is not NUL terminated. (The Windows signature below takes the out pointer and a
// pointer to the StringView; a hook written for it reads the size as a pointer, which is why the ArchiveXL hook on the
// same entry crashed.)
constexpr auto Create = Core::RawFunc<
    /* addr = */ Red::AddressLib::ResourcePath_Create,
    /* type = */ uint64_t (*)(const char* aData, uint32_t aSize)>();
#else
constexpr auto Create = Core::RawFunc<
    /* addr = */ Red::AddressLib::ResourcePath_Create,
    /* type = */ Red::ResourcePath* (*)(Red::ResourcePath* aOut, Red::StringView* aPathStr)>();
#endif
}
