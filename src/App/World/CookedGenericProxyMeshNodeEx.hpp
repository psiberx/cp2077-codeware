#pragma once

namespace App
{
struct CookedGenericProxyMeshNodeEx : Red::worldCookedGenericProxyMeshNode
{
    [[nodiscard]] int32_t GetInnerNodeCount()
    {
        auto innerNodes = GetInnerNodes();

        return static_cast<int32_t>(innerNodes.Size());
    }

    [[nodiscard]] Red::ScriptRef<Red::worldCookedGenericProxyMeshInnerNode> GetInnerNode(int32_t aIndex)
    {
        auto innerNodes = GetInnerNodes();

        if (aIndex < 0 || aIndex >= innerNodes.Size())
            return {};

        return {innerNodes[aIndex]};
    }
};
}

RTTI_EXPAND_CLASS(Red::worldCookedGenericProxyMeshNode, App::CookedGenericProxyMeshNodeEx, {
    RTTI_METHOD(GetInnerNodeCount);
    RTTI_METHOD(GetInnerNode);
});

RTTI_DEFINE_CLASS(Red::worldCookedGenericProxyMeshInnerNode, {
    RTTI_PROPERTY(mesh);
    RTTI_PROPERTY(meshAppearance);
    RTTI_PROPERTY(forceAutoHideDistance);
    RTTI_PROPERTY(lodLevelScales);
    RTTI_PROPERTY(occluderType);
    RTTI_PROPERTY(occluderAutohideDistanceScale);
    RTTI_PROPERTY(renderSceneLayerMask);
    RTTI_PROPERTY(castShadows);
    RTTI_PROPERTY(castLocalShadows);
    RTTI_PROPERTY(castRayTracedGlobalShadows);
    RTTI_PROPERTY(castRayTracedLocalShadows);
    RTTI_PROPERTY(windImpulseEnabled);
    RTTI_PROPERTY(removeFromRainMap);
    RTTI_PROPERTY(nbNodesUnderProxy);
    RTTI_PROPERTY(nearAutoHideDistance);
});
