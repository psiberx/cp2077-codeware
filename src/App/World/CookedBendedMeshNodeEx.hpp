#pragma once

namespace App
{
struct CookedBendedMeshNodeEx : Red::worldCookedBendedMeshNode
{
    [[nodiscard]] int32_t GetInnerNodeCount()
    {
        auto innerNodes = GetInnerNodes();

        return static_cast<int32_t>(innerNodes.Size());
    }

    [[nodiscard]] Red::ScriptRef<Red::worldCookedBendedMeshInnerNode> GetInnerNode(int32_t aIndex)
    {
        auto innerNodes = GetInnerNodes();

        if (aIndex < 0 || aIndex >= innerNodes.Size())
            return {};

        return {innerNodes[aIndex]};
    }
};
}

RTTI_EXPAND_CLASS(Red::worldCookedBendedMeshNode, App::CookedBendedMeshNodeEx, {
    RTTI_PROPERTY(deformationData);
    RTTI_PROPERTY(deformedBoxes);
    RTTI_METHOD(GetInnerNodeCount);
    RTTI_METHOD(GetInnerNode);
});

RTTI_DEFINE_CLASS(Red::worldCookedBendedMeshInnerNode, {
    RTTI_PROPERTY(mesh);
    RTTI_PROPERTY(meshAppearance);
    RTTI_PROPERTY(deformationDataStartIndex);
    RTTI_PROPERTY(deformationDataCount);
    RTTI_PROPERTY(index);
    RTTI_PROPERTY(castShadows);
    RTTI_PROPERTY(castLocalShadows);
    RTTI_PROPERTY(removeFromRainMap);
    RTTI_PROPERTY(isBendedRoad);
});
