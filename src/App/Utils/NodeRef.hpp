#pragma once

#include "Red/NodeRef.hpp"

namespace App
{
Red::NodeRef CreateNodeRef(Red::ScriptRef<Red::CString>& aReference)
{
    std::string_view reference{aReference.ref->c_str(), aReference.ref->Length()};

    Red::NodeRef instance;
    Raw::NodeRef::Create(instance, reference);

    return instance;
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
