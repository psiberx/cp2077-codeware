#pragma once

RTTI_DEFINE_CLASS(Red::worldCookedMeshInnerNode, {
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
});
