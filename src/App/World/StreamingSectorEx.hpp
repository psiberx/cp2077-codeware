#pragma once

#include "App/World/NodeSetupWrapper.hpp"
#include "Red/StreamingSector.hpp"

namespace App
{
struct StreamingSectorEx : Red::worldStreamingSector
{
    Red::DynArray<Red::Handle<Red::worldNode>> GetNodes()
    {
        auto& buffer = Raw::StreamingSector::NodeBuffer::Ref(this);
        return buffer.nodes;
    }

    int32_t GetNodeCount()
    {
        auto& buffer = Raw::StreamingSector::NodeBuffer::Ref(this);
        return static_cast<int32_t>(buffer.nodes.size);
    }

    Red::Handle<Red::worldNode> GetNode(int32_t aIndex)
    {
        auto& buffer = Raw::StreamingSector::NodeBuffer::Ref(this);
        if (aIndex >= 0 && aIndex < buffer.nodes.size)
            return buffer.nodes[aIndex];
        return {};
    }

    int32_t GetNodeSetupCount()
    {
        auto& buffer = Raw::StreamingSector::NodeBuffer::Ref(this);
        return static_cast<int32_t>(buffer.nodeSetups.GetInstanceCount());
    }

    Red::Handle<WorldNodeSetupWrapper> GetNodeSetup(int32_t aIndex)
    {
        auto* buffer = Raw::StreamingSector::NodeBuffer::Ptr(this);
        if (aIndex >= 0 && aIndex < buffer->nodeSetups.GetInstanceCount())
            return Red::MakeHandle<WorldNodeSetupWrapper>(buffer, buffer->nodeSetups.GetInstance(aIndex));
        return {};
    }
    Red::DynArray<Red::NodeRef> GetNodeRefs()
    {
        auto& buffer = Raw::StreamingSector::NodeBuffer::Ref(this);
        return buffer.nodeRefs;
    }

    int32_t GetNodeRefCount()
    {
        auto& buffer = Raw::StreamingSector::NodeBuffer::Ref(this);
        return static_cast<int32_t>(buffer.nodeRefs.size);
    }

    Red::NodeRef GetNodeRef(int32_t aIndex)
    {
        auto& buffer = Raw::StreamingSector::NodeBuffer::Ref(this);
        if (aIndex >= 0 && aIndex < buffer.nodeRefs.size)
            return buffer.nodeRefs[aIndex];
        return {};
    }

    void SetNodeRef(int32_t aIndex, Red::NodeRef aNodeRef)
    {
        auto& buffer = Raw::StreamingSector::NodeBuffer::Ref(this);
        if (aIndex >= 0 && aIndex < buffer.nodeRefs.size)
        {
            buffer.nodeRefs[aIndex] = aNodeRef;
        }
    }

    void AddNodeRef(Red::NodeRef aNodeRef)
    {
        auto& buffer = Raw::StreamingSector::NodeBuffer::Ref(this);
        buffer.nodeRefs.PushBack(aNodeRef);
    }
};
}

RTTI_EXPAND_CLASS(Red::worldStreamingSector, App::StreamingSectorEx, {
    RTTI_METHOD(GetNodes);
    RTTI_METHOD(GetNodeCount);
    RTTI_METHOD(GetNode);
    RTTI_METHOD(GetNodeSetupCount);
    RTTI_METHOD(GetNodeSetup);
    RTTI_METHOD(GetNodeRefs);
    RTTI_METHOD(GetNodeRefCount);
    RTTI_METHOD(GetNodeRef);
});
