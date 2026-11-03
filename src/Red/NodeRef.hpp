#pragma once

namespace Red
{
inline NodeRef ResolveNodeRef(NodeRef aNodeRef, GlobalNodeRef aContext = GlobalNodeRef::GlobalRoot)
{
    GlobalNodeRef resolved{};
    CallGlobal("ResolveNodeRef", resolved, aNodeRef, aContext);

    return resolved.hash;
}

inline EntityID ResolveEntityID(NodeRef aNodeRef, GlobalNodeRef aContext = GlobalNodeRef::GlobalRoot)
{
    return ResolveNodeRef(aNodeRef).hash;
}
}

namespace Raw::NodeRef
{
constexpr auto Create = Core::RawFunc<
    /* addr = */ Red::AddressLib::NodeRef_Create,
    /* type = */ Red::NodeRef* (*)(Red::NodeRef& aOut, Red::StringView& aReference)>();

#if defined(__APPLE__)
// R13. Same function at 0x3340CF8, Mac ABI. The game walks the '#' '$' '~' prefixes and the '/' segments,
// returns the hash in x0, or 0 on failure or an empty string.
constexpr auto CreateMac = Core::RawFunc<
    /* addr = */ Red::AddressLib::NodeRef_Create,
    /* type = */ uint64_t (*)(const char* aStr, uint32_t aLength, bool aFlag)>();
#endif
}
