#pragma once

#include "Addresses.hpp"
#include "Red/Strings.hpp"

namespace Red
{
inline NodeRef ResolveNodeRef(NodeRef aNodeRef, NodeRef aContext = NodeRef::GlobalRoot)
{
    GlobalNodeRef resolved{};
    CallGlobal("ResolveNodeRef", resolved, aNodeRef, aContext);

    return resolved.hash;
}

inline EntityID ResolveEntityID(NodeRef aNodeRef, NodeRef aContext = NodeRef::GlobalRoot)
{
    return ResolveNodeRef(aNodeRef).hash;
}
}

namespace Raw::NodeRef
{
constexpr auto Create = Core::RawFunc<
    /* addr = */ Red::Addresses::NodeRef_Create,
    /* type = */ Red::NodeRef* (*)(Red::NodeRef& aOut, Red::StringView& aReference)>();
}
