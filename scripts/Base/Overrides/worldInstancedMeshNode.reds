public native struct worldInstancedMeshInnerNode {
    public native let groupWorldBoundingBox: Box;
    public native let mesh: ResourceAsyncRef; // raRef<CMesh>
    public native let meshAppearance: CName;
    public native let forceAutoHideDistance: Float;
    public native let lodLevelScales: Uint32;
    public native let castShadows: shadowsShadowCastingMode;
    public native let castLocalShadows: shadowsShadowCastingMode;
    public native let renderSceneLayerMask: Uint8;
    public native let occluderType: visWorldOccluderType;
    public native let occluderAutoHideDistanceScale: Uint8;
    public native let removeFromRainMap: Bool;
}

public native struct worldInstancedMeshNodeTranformRange {
    public native let transformStartIndex: Uint16;
    public native let numTransforms: Uint16;
}

public native class worldInstancedMeshNode extends worldCookedNode {
    public native let cookedInstances: array<worldInstancedMeshInnerNode>;
    public native let transformRanges: array<worldInstancedMeshNodeTranformRange>;
    public native let version: Uint8;

    public native func GetTransformCount() -> Int32
    public native func GetTransform(index: Int32) -> script_ref<worldNodeTransform>
}
