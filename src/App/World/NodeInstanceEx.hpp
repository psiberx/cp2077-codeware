#pragma once

#include "Red/WorldNode.hpp"

namespace App
{
struct NodeInstanceEx : Red::worldINodeInstance
{
    [[nodiscard]] Red::Handle<Red::worldNode> GetNode() const
    {
        return Raw::WorldNodeInstance::Node::Ref(this);
    }

    [[nodiscard]] Red::Transform GetTransform() const
    {
        return Raw::WorldNodeInstance::Transform::Ref(this);
    }

    [[nodiscard]] Red::Vector3 GetScale() const
    {
        return Raw::WorldNodeInstance::Scale::Ref(this);
    }

    [[nodiscard]] Red::GlobalNodeID GetGlobalNodeID() const
    {
        return {Raw::WorldNodeInstance::SetupInfo::Ref(this)->globalNodeID};
    }

    [[nodiscard]] Red::GlobalNodeID GetProxyNodeID() const
    {
        return {Raw::WorldNodeInstance::SetupInfo::Ref(this)->proxyNodeID};
    }

    [[nodiscard]] float GetStreamingDistance() const
    {
        return Raw::WorldNodeInstance::SetupInfo::Ref(this)->streamingDistance;
    }
};
}

RTTI_EXPAND_CLASS(Red::worldINodeInstance, App::NodeInstanceEx, {
    RTTI_METHOD(GetNode);
    RTTI_METHOD(GetTransform);
    RTTI_METHOD(GetScale);
    RTTI_METHOD(GetGlobalNodeID);
    RTTI_METHOD(GetProxyNodeID);
    RTTI_METHOD(GetStreamingDistance);
});
