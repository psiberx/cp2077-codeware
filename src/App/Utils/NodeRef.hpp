#pragma once

#include "Red/NodeRef.hpp"

namespace App
{
Red::NodeRef CreateNodeRef(Red::ScriptRef<Red::CString>& aReference)
{
    Red::NodeRef nodeRef{};
    Red::StringView nodeRefStr{*aReference.ref};
#if defined(__APPLE__)
    // R13. The Mac game function takes (str, len, flag) and returns the hash.
    nodeRef.hash = Raw::NodeRef::CreateMac(nodeRefStr.ptr, nodeRefStr.length, false);
#else
    Raw::NodeRef::Create(nodeRef, nodeRefStr);
#endif

    return nodeRef;
}

Red::NodeRef HashToNodeRef(uint64_t aRef)
{
    return aRef;
}

uint64_t NodeRefToHash(Red::NodeRef aRef)
{
    return aRef;
}
}

RTTI_DEFINE_GLOBALS({
    RTTI_FUNCTION(App::CreateNodeRef);
    RTTI_FUNCTION(App::HashToNodeRef);
    RTTI_FUNCTION(App::NodeRefToHash);
});
