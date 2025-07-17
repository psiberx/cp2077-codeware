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
}
