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
        if (sector->buffer.version >= 68)
        {
            return static_cast<uint16_t>(setup->nodeIndex);
        }
        else
        {
            return setup->v62.nodeIndex;
        }
    }

    [[nodiscard]] uint32_t GetInstanceIndex() const
    {
        if (sector->buffer.version >= 68)
        {
            return setup->instanceIndex;
        }
        else
        {
            return std::numeric_limits<uint32_t>::max();
        }
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

    [[nodiscard]] Red::Vector3 GetStreamingPosition() const
    {
        return setup->streamingRefPoint;
    }

    [[nodiscard]] Red::Vector3 GetSecondaryRefPointPosition() const
    {
        return setup->secondaryRefPointPosition;
    }

    [[nodiscard]] Red::Vector3 GetPreboostStreamingRefPointPosition() const
    {
        return setup->preboostStreamingRefPoint;
    }

    [[nodiscard]] float GetStreamingDistance() const
    {
        if (sector->buffer.version >= 68)
        {
            return setup->streamingDistance;
        }
        else
        {
            return setup->v62.streamingDistance;
        }
    }

    [[nodiscard]] float GetSecondaryRefPointDistance() const
    {
        if (sector->buffer.version >= 68)
        {
            return setup->secondaryRefPointDistance;
        }
        else
        {
            return setup->v62.secondaryRefPointDistance;
        }
    }

    [[nodiscard]] Red::worldStreamingDataGroup GetDataGroup() const
    {
        if (sector->buffer.version >= 68)
        {
            return setup->dataGroup;
        }
        else
        {
            return Red::worldStreamingDataGroup::Base;
        }
    }

    void SetNodeIndex(uint16_t aIndex) const
    {
        if (aIndex >= 0 && aIndex < sector->buffer.nodeSetups.Size())
        {
            if (sector->buffer.version >= 68)
            {
                setup->nodeIndex = aIndex;
            }
            else
            {
                setup->v62.nodeIndex = aIndex;
            }

            setup->node = sector->nodes[aIndex].instance;
        }
    }

    void SetInstanceIndex(uint32_t aIndex) const
    {
        if (sector->buffer.version >= 68)
        {
            setup->instanceIndex = aIndex;
        }
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

    void SetStreamingPosition(const Red::Vector3& aPosition) const
    {
        setup->streamingRefPoint = aPosition;
    }

    void SetSecondaryRefPointPosition(const Red::Vector3& aPosition) const
    {
        setup->secondaryRefPointPosition = aPosition;
    }

    void SetPreboostStreamingRefPointPosition(const Red::Vector3& aPosition) const
    {
        setup->preboostStreamingRefPoint = aPosition;
    }

    void SetStreamingDistance(float aDistance) const
    {
        if (sector->buffer.version >= 68)
        {
            setup->streamingDistance = aDistance;
        }
        else
        {
            setup->v62.streamingDistance = aDistance;
        }
    }

    void SetSecondaryRefPointDistance(float aDistance) const
    {
        if (sector->buffer.version >= 68)
        {
            setup->secondaryRefPointDistance = aDistance;
        }
        else
        {
            setup->v62.secondaryRefPointDistance = aDistance;
        }
    }

    void SetDataGroup(Red::worldStreamingDataGroup aGroup) const
    {
        if (sector->buffer.version >= 68)
        {
            setup->dataGroup = aGroup;
        }
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
    RTTI_METHOD(GetInstanceIndex);
    RTTI_METHOD(GetTransform);
    RTTI_METHOD(GetPosition);
    RTTI_METHOD(GetOrientation);
    RTTI_METHOD(GetScale);
    RTTI_METHOD(GetNodeRef);
    RTTI_METHOD(GetGlobalNodeID);
    RTTI_METHOD(GetProxyNodeID);
    RTTI_METHOD(GetStreamingPosition);
    RTTI_METHOD(GetSecondaryRefPointPosition);
    RTTI_METHOD(GetPreboostStreamingRefPointPosition);
    RTTI_METHOD(GetStreamingDistance);
    RTTI_METHOD(GetSecondaryRefPointDistance);
    RTTI_METHOD(GetDataGroup);
    RTTI_METHOD(SetNodeIndex);
    RTTI_METHOD(SetInstanceIndex);
    RTTI_METHOD(SetTransform);
    RTTI_METHOD(SetPosition);
    RTTI_METHOD(SetOrientation);
    RTTI_METHOD(SetScale);
    RTTI_METHOD(SetNodeRef);
    RTTI_METHOD(SetGlobalNodeID);
    RTTI_METHOD(SetProxyNodeID);
    RTTI_METHOD(SetStreamingPosition);
    RTTI_METHOD(SetSecondaryRefPointPosition);
    RTTI_METHOD(SetPreboostStreamingRefPointPosition);
    RTTI_METHOD(SetStreamingDistance);
    RTTI_METHOD(SetSecondaryRefPointDistance);
    RTTI_METHOD(SetDataGroup);
});
