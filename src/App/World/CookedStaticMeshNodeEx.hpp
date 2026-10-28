#pragma once

namespace App
{
struct CookedStaticMeshNodeEx : Red::worldCookedStaticMeshNode
{
    [[nodiscard]] int32_t GetInnerNodeCount()
    {
        auto innerNodes = GetInnerNodes();

        return static_cast<int32_t>(innerNodes.Size());
    }

    [[nodiscard]] Red::ScriptRef<Red::worldCookedMeshInnerNode> GetInnerNode(int32_t aIndex)
    {
        auto innerNodes = GetInnerNodes();

        if (aIndex < 0 || aIndex >= innerNodes.Size())
            return {};

        return {innerNodes[aIndex]};
    }
};
}

RTTI_EXPAND_CLASS(Red::worldCookedStaticMeshNode, App::CookedStaticMeshNodeEx, {
    RTTI_METHOD(GetInnerNodeCount);
    RTTI_METHOD(GetInnerNode);
});
