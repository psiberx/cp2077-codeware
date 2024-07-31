#pragma once

#include "Red/StreamingSector.hpp"

namespace App
{
struct WorldNodeSetupWrapper : Red::IScriptable
{
    WorldNodeSetupWrapper() = default;

    WorldNodeSetupWrapper(Red::CompiledNodeInstanceSetupInfo* aSetup)
        : setup(aSetup)
    {
    }

    WorldNodeSetupWrapper(const WorldNodeSetupWrapper&) = default;
    WorldNodeSetupWrapper(WorldNodeSetupWrapper&&) = default;

    [[nodiscard]] Red::Handle<Red::worldNode> GetNode() const
    {
        return Red::AsHandle(setup->node);
    }

    [[nodiscard]] Red::Transform GetTransform() const
    {
        return setup->transform;
    }

    [[nodiscard]] Red::Vector4 GetPosition() const
    {
        return setup->transform.position;
    }

    [[nodiscard]] Red::Quaternion GetOrientation() const
    {
        return setup->transform.orientation;
    }

    [[nodiscard]] Red::Vector3 GetScale() const
    {
        return setup->scale;
    }

    [[nodiscard]] Red::NodeRef GetNodeRef() const
    {
        return {setup->globalNodeID};
    }

    [[nodiscard]] Red::GlobalNodeID GetGlobalNodeID() const
    {
        return {setup->globalNodeID};
    }

    [[nodiscard]] Red::GlobalNodeID GetProxyNodeID() const
    {
        return {setup->proxyNodeID};
    }

    [[nodiscard]] float GetStreamingDistance() const
    {
        return setup->streamingDistance;
    }

    void SetTransform(const Red::Transform& aTransform) const
    {
        setup->transform = aTransform;
    }

    void SetPosition(const Red::Vector4& aPosition) const
    {
        setup->transform.position = aPosition;
    }

    void SetOrientation(const Red::Quaternion& aOrientation) const
    {
        setup->transform.orientation = aOrientation;
    }

    void SetScale(const Red::Vector3& aScale) const
    {
        setup->scale = aScale;
    }

    void SetNodeRef(Red::NodeRef aNodeRef) const
    {
        setup->globalNodeID = aNodeRef.hash;
    }

    void SetGlobalNodeID(Red::GlobalNodeID aNodeID) const
    {
        setup->globalNodeID = aNodeID.hash;
    }

    void SetProxyNodeID(Red::GlobalNodeID aProxyID) const
    {
        setup->proxyNodeID = aProxyID.hash;
    }

    void SetStreamingDistance(float aDistance) const
    {
        setup->streamingDistance = aDistance;
    }

    Red::CompiledNodeInstanceSetupInfo* setup{};

    RTTI_IMPL_TYPEINFO(App::WorldNodeSetupWrapper);
    RTTI_IMPL_ALLOCATOR();
};
}

RTTI_DEFINE_CLASS(App::WorldNodeSetupWrapper, {
    RTTI_METHOD(GetNode);
    RTTI_METHOD(GetTransform);
    RTTI_METHOD(GetPosition);
    RTTI_METHOD(GetOrientation);
    RTTI_METHOD(GetScale);
    RTTI_METHOD(GetNodeRef);
    RTTI_METHOD(GetGlobalNodeID);
    RTTI_METHOD(GetProxyNodeID);
    RTTI_METHOD(GetStreamingDistance);
    RTTI_METHOD(SetTransform);
    RTTI_METHOD(SetPosition);
    RTTI_METHOD(SetOrientation);
    RTTI_METHOD(SetScale);
    RTTI_METHOD(SetNodeRef);
    RTTI_METHOD(SetGlobalNodeID);
    RTTI_METHOD(SetProxyNodeID);
    RTTI_METHOD(SetStreamingDistance);
});
