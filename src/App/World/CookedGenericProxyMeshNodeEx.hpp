#pragma once

namespace App
{
struct CookedGenericProxyMeshNodeEx : Red::worldCookedGenericProxyMeshNode
{
    // GetInnerNodeCount() and GetInnerNode() are inherited from worldCookedMeshNode.
    // This returns the full proxy inner node; it has its own name because a script
    // override can't change the return type.
    [[nodiscard]] Red::ScriptRef<Red::worldCookedGenericProxyMeshInnerNode> GetProxyInnerNode(int32_t aIndex)
    {
        auto innerNodes = GetInnerNodes();

        if (aIndex < 0 || aIndex >= innerNodes.Size())
            return {};

        return {innerNodes[aIndex]};
    }
};
}

RTTI_EXPAND_CLASS(Red::worldCookedGenericProxyMeshNode, App::CookedGenericProxyMeshNodeEx, {
    RTTI_METHOD(GetProxyInnerNode);
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
