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

    [[nodiscard]] Red::Vector3 GetScale() const
    {
        return setup->scale;
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

    void SetScale(const Red::Vector3& aScale) const
    {
        setup->scale = aScale;
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
    RTTI_METHOD(GetScale);
    RTTI_METHOD(GetGlobalNodeID);
    RTTI_METHOD(GetProxyNodeID);
    RTTI_METHOD(GetStreamingDistance);
    RTTI_METHOD(SetTransform);
    RTTI_METHOD(SetScale);
    RTTI_METHOD(SetGlobalNodeID);
    RTTI_METHOD(SetProxyNodeID);
    RTTI_METHOD(SetStreamingDistance);
});
