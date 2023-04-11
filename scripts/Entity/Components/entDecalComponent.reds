public native class entDecalComponent extends IVisualComponent {
  native let material: ResourceRef;
  native let verticalFlip: Bool;
  native let horizontalFlip: Bool;
  native let aspectRatio: Float;
  native let scale: Float;
  native let visualScale: Vector3;
  native let alpha: Float;
  native let normalThreshold: Float;
  native let roughnessScale: Float;
  native let orderNo: Uint16;
  native let surfaceType: ERenderObjectType;
  native let decalRenderMode: EDecalRenderMode;
  native let isStretchingEnabled: Bool;
  native let normalsBlendingMode: RenderDecalNormalsBlendingMode;
  native let shouldCollectWithRayTracing: Bool;
  native let isEnabled: Bool;
}
