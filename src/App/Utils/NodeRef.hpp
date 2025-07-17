#pragma once

#include "Red/NodeRef.hpp"

namespace App
{
Red::NodeRef CreateNodeRef(Red::ScriptRef<Red::CString>& aReference)
{
    Red::NodeRef nodeRef{};
    Red::StringView nodeRefStr{*aReference.ref};
    Raw::NodeRef::Create(nodeRef, nodeRefStr);

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
