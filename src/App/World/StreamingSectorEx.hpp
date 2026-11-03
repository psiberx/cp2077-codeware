#pragma once

#include "App/World/NodeSetupWrapper.hpp"

namespace App
{
struct StreamingSectorEx : Red::worldStreamingSector
{
    Red::DynArray<Red::Handle<Red::worldNode>> GetNodes()
    {
        return compiled.nodes;
    }

    int32_t GetNodeCount()
    {
        return static_cast<int32_t>(compiled.nodes.Size());
    }

    Red::Handle<Red::worldNode> GetNode(int32_t aIndex)
    {
        if (aIndex >= 0 && aIndex < compiled.nodes.Size())
            return compiled.nodes[aIndex];
        return {};
    }

    int32_t GetNodeSetupCount()
    {
        return static_cast<int32_t>(compiled.buffer.nodeSetups.Size());
    }

    Red::Handle<WorldNodeSetupWrapper> GetNodeSetup(int32_t aIndex)
    {
        if (aIndex >= 0 && aIndex < compiled.buffer.nodeSetups.Size())
        {
            return Red::MakeHandle<WorldNodeSetupWrapper>(&compiled, &compiled.buffer.nodeSetups.At(aIndex));
        }

        return {};
    }
    Red::DynArray<Red::NodeRef> GetNodeRefs()
    {
        return compiled.nodeRefs;
    }

    int32_t GetNodeRefCount()
    {
        return static_cast<int32_t>(compiled.nodeRefs.Size());
    }

    Red::NodeRef GetNodeRef(int32_t aIndex)
    {
        if (aIndex >= 0 && aIndex < compiled.nodeRefs.Size())
            return compiled.nodeRefs[aIndex];
        return {};
    }

    void SetNodeRef(int32_t aIndex, Red::NodeRef aNodeRef)
    {
        if (aIndex >= 0 && aIndex < compiled.nodeRefs.Size())
        {
            compiled.nodeRefs[aIndex] = aNodeRef;
        }
    }

    void AddNodeRef(Red::NodeRef aNodeRef)
    {
        compiled.nodeRefs.PushBack(aNodeRef);
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
