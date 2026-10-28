public native struct worldCookedGenericProxyMeshInnerNode {
    public native let mesh: ResourceAsyncRef; // raRef<CMesh>
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
    public native let nbNodesUnderProxy: Uint32;
    public native let nearAutoHideDistance: Float;
}

public native class worldCookedGenericProxyMeshNode extends worldCookedPrefabProxyMeshNode {
    public native func GetInnerNodeCount() -> Int32
    public native func GetInnerNode(index: Int32) -> script_ref<worldCookedGenericProxyMeshInnerNode>
}
