public native struct worldCookedBendedMeshInnerNode {
    public native let mesh: ResourceAsyncRef; // raRef<CMesh>
    public native let meshAppearance: CName;
    public native let deformationDataStartIndex: Uint32;
    public native let deformationDataCount: Uint32;
    public native let index: Uint16;
    public native let castShadows: shadowsShadowCastingMode;
    public native let castLocalShadows: shadowsShadowCastingMode;
    public native let removeFromRainMap: Bool;
    public native let isBendedRoad: Bool;
}

public native class worldCookedBendedMeshNode extends worldCookedNode {
    public native let deformationData: array<Matrix>;
    public native let deformedBoxes: array<Box>;

    public native func GetInnerNodeCount() -> Int32
    public native func GetInnerNode(index: Int32) -> script_ref<worldCookedBendedMeshInnerNode>
}
