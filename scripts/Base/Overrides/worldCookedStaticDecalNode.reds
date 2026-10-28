public native struct worldCookedStaticDecalInnerNode {
    public native let material: ResourceAsyncRef; // raRef<IMaterial>
    public native let forcedAutoHideDistance: Float;
    public native let autoHideDistance: Float;
    public native let alpha: Float;
    public native let normalThreshold: Float;
    public native let roughnessScale: Float;
    public native let orderNo: Uint16;
    public native let diffuseColorScaleIndex: Uint16;
    public native let surfaceType: ERenderObjectType;
    public native let decalRenderMode: EDecalRenderMode;
    public native let normalsBlendingMode: RenderDecalNormalsBlendingMode;
    public native let flags: Uint8;
}

public native class worldCookedStaticDecalNode extends worldCookedNode {
    public native let diffuseColorScales: array<HDRColor>;

    public native func GetInnerNodeCount() -> Int32
    public native func GetInnerNode(index: Int32) -> script_ref<worldCookedStaticDecalInnerNode>
}
