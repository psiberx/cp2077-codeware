public native struct worldCookedMeshInnerNode {
    public native let mesh: ResRef;
    public native let meshAppearance: CName;
    public native let forceAutoHideDistance: Float;
    public native let lodLevelScales: Uint32;
    public native let occluderType: visWorldOccluderType;
    public native let occluderAutohideDistanceScale: Uint8;
    public native let renderSceneLayerMask: Uint8;
    public native let castShadows: shadowsShadowCastingMode;
    public native let castLocalShadows: shadowsShadowCastingMode;
    public native let castRayTracedGlobalShadows: shadowsShadowCastingMode;
    public native let castRayTracedLocalShadows: shadowsShadowCastingMode;
    public native let windImpulseEnabled: Bool;
    public native let removeFromRainMap: Bool;
}

public native class worldCookedMeshNode extends worldCookedNode {}
