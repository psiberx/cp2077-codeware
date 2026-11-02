#pragma once

namespace App
{
struct WorldNodeSetupWrapper : Red::IScriptable
{
    WorldNodeSetupWrapper() = default;

    WorldNodeSetupWrapper(Red::worldCompiledSector* aSector,
                          Red::worldCompiledNodeInstanceSetupInfo* aSetup)
        : sector(aSector)
        , setup(aSetup)
    {
    }

    WorldNodeSetupWrapper(const WorldNodeSetupWrapper&) = default;
    WorldNodeSetupWrapper(WorldNodeSetupWrapper&&) = default;

    [[nodiscard]] Red::Handle<Red::worldNode> GetNode() const
    {
        return Red::AsHandle(setup->node);
    }

    [[nodiscard]] uint16_t GetNodeIndex() const
    {
        return setup->GetNodeIndex(sector->buffer.version);
    }

    void SetNodeIndex(uint16_t aIndex) const
    {
        if (aIndex >= 0 && aIndex < sector->buffer.nodeSetups.Size())
        {
            setup->SetNodeIndex(sector->buffer.version, aIndex);
            setup->node = sector->nodes[aIndex].instance;
        }
    }

    [[nodiscard]] uint32_t GetInnerNodeIndex() const
    {
        return setup->GetInnerNodeIndex(sector->buffer.version);
    }

    void SetInnerNodeIndex(uint32_t aIndex) const
    {
        setup->SetInnerNodeIndex(sector->buffer.version, aIndex);
    }

    [[nodiscard]] Red::Transform GetTransform() const
    {
        return setup->transform;
    }

    void SetTransform(const Red::Transform& aTransform) const
    {
        setup->transform = aTransform;
    }

    [[nodiscard]] Red::Vector4 GetPosition() const
    {
        return setup->transform.position;
    }

    void SetPosition(const Red::Vector4& aPosition) const
    {
        setup->transform.position = aPosition;
    }

    [[nodiscard]] Red::Quaternion GetOrientation() const
    {
        return setup->transform.orientation;
    }

    void SetOrientation(const Red::Quaternion& aOrientation) const
    {
        setup->transform.orientation = aOrientation;
    }

    [[nodiscard]] Red::Vector3 GetScale() const
    {
        return setup->scale;
    }

    void SetScale(const Red::Vector3& aScale) const
    {
        setup->scale = aScale;
    }

    [[nodiscard]] Red::NodeRef GetNodeRef() const
    {
        return {setup->globalNodeID};
    }

    void SetNodeRef(Red::NodeRef aNodeRef) const
    {
        setup->globalNodeID = aNodeRef.hash;
    }

    [[nodiscard]] Red::GlobalNodeID GetGlobalNodeID() const
    {
        return {setup->globalNodeID};
    }

    void SetGlobalNodeID(Red::GlobalNodeID aNodeID) const
    {
        setup->globalNodeID = aNodeID.hash;
    }

    [[nodiscard]] Red::GlobalNodeID GetProxyNodeID() const
    {
        return {setup->proxyNodeID};
    }

    void SetProxyNodeID(Red::GlobalNodeID aProxyID) const
    {
        setup->proxyNodeID = aProxyID.hash;
    }

    [[nodiscard]] Red::Vector3 GetStreamingPosition() const
    {
        return setup->streamingRefPoint;
    }

    void SetStreamingPosition(const Red::Vector3& aPosition) const
    {
        setup->streamingRefPoint = aPosition;
    }

    [[nodiscard]] Red::Vector3 GetSecondaryRefPointPosition() const
    {
        return setup->secondaryRefPointPosition;
    }

    [[nodiscard]] float GetStreamingDistance() const
    {
        return setup->GetStreamingDistance(sector->buffer.version);
    }

    void SetStreamingDistance(float aDistance) const
    {
        setup->SetStreamingDistance(sector->buffer.version, aDistance);
    }

    void SetSecondaryRefPointPosition(const Red::Vector3& aPosition) const
    {
        setup->secondaryRefPointPosition = aPosition;
    }

    [[nodiscard]] float GetSecondaryRefPointDistance() const
    {
        return setup->GetSecondaryRefPointDistance(sector->buffer.version);
    }

    void SetSecondaryRefPointDistance(float aDistance) const
    {
        setup->SetSecondaryRefPointDistance(sector->buffer.version, aDistance);
    }

    [[nodiscard]] Red::Vector3 GetPreboostStreamingRefPointPosition() const
    {
        return setup->preboostStreamingRefPoint;
    }

    void SetPreboostStreamingRefPointPosition(const Red::Vector3& aPosition) const
    {
        setup->preboostStreamingRefPoint = aPosition;
    }

    [[nodiscard]] uint8_t GetStreamingPriority() const
    {
        return setup->GetStreamingPriority(sector->buffer.version);
    }

    void SetStreamingPriority(uint8_t aPriority) const
    {
        setup->SetStreamingPriority(sector->buffer.version, aPriority);
    }

    [[nodiscard]] uint16_t GetTimeOfDayVisibilityMask() const
    {
        return setup->GetTimeOfDayVisibilityMask(sector->buffer.version);
    }

    void SetTimeOfDayVisibilityMask(uint16_t aMask) const
    {
        setup->SetTimeOfDayVisibilityMask(sector->buffer.version, aMask);
    }

    [[nodiscard]] Red::worldStreamingDataGroup GetDataGroup() const
    {
        return setup->GetDataGroup(sector->buffer.version);
    }

    void SetDataGroup(Red::worldStreamingDataGroup aGroup) const
    {
        setup->SetDataGroup(sector->buffer.version, aGroup);
    }

    Red::worldCompiledSector* sector{};
    Red::worldCompiledNodeInstanceSetupInfo* setup{};

    RTTI_IMPL_TYPEINFO(App::WorldNodeSetupWrapper);
    RTTI_IMPL_ALLOCATOR();
};
}

RTTI_DEFINE_CLASS(App::WorldNodeSetupWrapper, {
    RTTI_METHOD(GetNode);
    RTTI_METHOD(GetNodeIndex);
    RTTI_METHOD(SetNodeIndex);
    RTTI_METHOD(GetInnerNodeIndex);
    RTTI_METHOD(SetInnerNodeIndex);
    RTTI_METHOD(GetTransform);
    RTTI_METHOD(SetTransform);
    RTTI_METHOD(GetPosition);
    RTTI_METHOD(SetPosition);
    RTTI_METHOD(GetOrientation);
    RTTI_METHOD(SetOrientation);
    RTTI_METHOD(GetScale);
    RTTI_METHOD(SetScale);
    RTTI_METHOD(GetNodeRef);
    RTTI_METHOD(SetNodeRef);
    RTTI_METHOD(GetGlobalNodeID);
    RTTI_METHOD(SetGlobalNodeID);
    RTTI_METHOD(GetProxyNodeID);
    RTTI_METHOD(SetProxyNodeID);
    RTTI_METHOD(GetStreamingPosition);
    RTTI_METHOD(SetStreamingPosition);
    RTTI_METHOD(GetSecondaryRefPointPosition);
    RTTI_METHOD(SetSecondaryRefPointPosition);
    RTTI_METHOD(GetPreboostStreamingRefPointPosition);
    RTTI_METHOD(SetPreboostStreamingRefPointPosition);
    RTTI_METHOD(GetStreamingDistance);
    RTTI_METHOD(SetStreamingDistance);
    RTTI_METHOD(GetSecondaryRefPointDistance);
    RTTI_METHOD(SetSecondaryRefPointDistance);
    RTTI_METHOD(GetStreamingPriority);
    RTTI_METHOD(SetStreamingPriority);
    RTTI_METHOD(GetTimeOfDayVisibilityMask);
    RTTI_METHOD(SetTimeOfDayVisibilityMask);
    RTTI_METHOD(GetDataGroup);
    RTTI_METHOD(SetDataGroup);
});
