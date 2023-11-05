#pragma once

#include "Red/NodeRef.hpp"

namespace App
{
Red::NodeRef CreateNodeRef(Red::ScriptRef<Red::CString>& aReference)
{
    Red::NodeRef nodeRef{};
    Red::StringView nodeRefStr{aReference.ref->c_str(), aReference.ref->Length()};
    Raw::NodeRef::Create(nodeRef, nodeRefStr);

    return nodeRef;
}

uint64_t NodeRefToHash(Red::NodeRef aRef)
{
    return aRef.hash;
}
}

RTTI_DEFINE_GLOBALS({
    RTTI_FUNCTION(App::CreateNodeRef);
    RTTI_FUNCTION(App::NodeRefToHash);
});
