#pragma once

#include "Red/Debug.hpp"
#include "Red/NodeRef.hpp"

namespace App
{
Red::CString InspectHash(uint64_t aHash)
{
    if (!aHash)
        return {};

    {
        static const Red::GlobalNodeRef context{Red::FNV1a64("$")};

        Red::NodeRef nodeRef{aHash};
        Red::GlobalNodeRef resolvedRef{};
        Red::CallGlobal("ResolveNodeRef", resolvedRef, nodeRef, context);

        if (resolvedRef.hash != 0)
        {
            aHash = resolvedRef.hash;
        }
    }

    Red::CString debugStr;

    {
        Red::EntityID entityID{aHash};
        Raw::EntityID::ToStringDEBUG(entityID, debugStr);

        if (debugStr.Length() != 0)
        {
            std::string_view debugStrView(debugStr.c_str(), debugStr.Length());
            if (!debugStrView.starts_with("UNKNOWN:") && !debugStrView.starts_with("dynamic:"))
                return debugStr;
        }
    }

    {
        Red::CName name{aHash};
        const auto resolvedName = name.ToString();

        if (resolvedName)
            return resolvedName;
    }

    {
        Red::TweakDBID tweakDBID{aHash};
        Red::CallStatic("gamedataTDBIDHelper", "ToStringDEBUG", debugStr, tweakDBID);

        if (debugStr.Length() != 0)
            return debugStr;
    }

    return {};
}

Red::CString InspectRef(const Red::CString& aReference)
{
    Red::NodeRef nodeRef{};
    Red::StringView nodeRefStr{aReference.c_str(), aReference.Length()};
    Raw::NodeRef::Create(nodeRef, nodeRefStr);

    return InspectHash(nodeRef.hash);
}
}

RTTI_DEFINE_GLOBALS({
    RTTI_FUNCTION(App::InspectHash);
    RTTI_FUNCTION(App::InspectRef);
});
