public native class entDecalComponent extends IVisualComponent {
  public native let material: ResourceRef; // rRef<IMaterial>
  public native let verticalFlip: Bool;
  public native let horizontalFlip: Bool;
  public native let aspectRatio: Float;
  public native let scale: Float;
  public native let visualScale: Vector3;
  public native let alpha: Float;
  public native let normalThreshold: Float;
  public native let roughnessScale: Float;
  public native let orderNo: Uint16;
  public native let surfaceType: ERenderObjectType;
  public native let decalRenderMode: EDecalRenderMode;
  public native let isStretchingEnabled: Bool;
  public native let normalsBlendingMode: RenderDecalNormalsBlendingMode;
  public native let shouldCollectWithRayTracing: Bool;
  public native let isEnabled: Bool;
}
