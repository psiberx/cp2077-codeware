#pragma once

namespace App
{
struct InstancedMeshNodeEx : Red::worldInstancedMeshNode
{
    [[nodiscard]] int32_t GetTransformCount()
    {
        return static_cast<int32_t>(cookedWorldTransformsBuffer.Size());
    }

    [[nodiscard]] Red::ScriptRef<Red::rendRenderProxyTransform> GetTransform(int32_t aIndex)
    {
        if (aIndex < 0 || aIndex >= cookedWorldTransformsBuffer.Size())
            return {};

        return {cookedWorldTransformsBuffer[aIndex]};
    }
};
}

RTTI_EXPAND_CLASS(Red::worldInstancedMeshNode, App::InstancedMeshNodeEx, {
    RTTI_PROPERTY(cookedInstances);
    RTTI_PROPERTY(transformRanges);
    RTTI_METHOD(GetTransformCount);
    RTTI_METHOD(GetTransform);
});

RTTI_DEFINE_CLASS(Red::worldInstancedMeshInnerNode, {
    RTTI_PROPERTY(groupWorldBoundingBox);
    RTTI_PROPERTY(mesh);
    RTTI_PROPERTY(meshAppearance);
    RTTI_PROPERTY(forceAutoHideDistance);
    RTTI_PROPERTY(lodLevelScales);
    RTTI_PROPERTY(castShadows);
    RTTI_PROPERTY(castLocalShadows);
    RTTI_PROPERTY(renderSceneLayerMask);
    RTTI_PROPERTY(occluderType);
    RTTI_PROPERTY(occluderAutoHideDistanceScale);
    RTTI_PROPERTY(removeFromRainMap);
});

RTTI_DEFINE_CLASS(Red::worldInstancedMeshNodeTranformRange, {
    RTTI_PROPERTY(transformStartIndex);
    RTTI_PROPERTY(numTransforms);
});

RTTI_DEFINE_CLASS(Red::rendRenderProxyTransform, {
    RTTI_PROPERTY(transform);
    RTTI_PROPERTY(scale);
});
