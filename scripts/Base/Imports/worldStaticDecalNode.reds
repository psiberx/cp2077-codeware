public native class worldStaticDecalNode extends worldNode {
  public native let material: ResourceAsyncRef; // raRef<IMaterial>
  public native let autoHideDistance: Float;
  public native let verticalFlip: Bool;
  public native let horizontalFlip: Bool;
  public native let alpha: Float;
  public native let normalThreshold: Float;
  public native let roughnessScale: Float;
  public native let diffuseColorScale: HDRColor;
  public native let isStretchingEnabled: Bool;
  public native let enableNormalTreshold: Bool;
  public native let orderNo: Uint16;
  public native let surfaceType: ERenderObjectType;
  public native let normalsBlendingMode: RenderDecalNormalsBlendingMode;
  public native let decalRenderMode: EDecalRenderMode;
  public native let shouldCollectWithRayTracing: Bool;
  public native let forcedAutoHideDistance: Float;
  public native let decalNodeVersion: Uint8;
}
