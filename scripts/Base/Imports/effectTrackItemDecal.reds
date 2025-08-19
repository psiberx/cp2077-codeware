public native class effectTrackItemDecal extends effectTrackItem {
  public native let material: ResourceRef; // rRef<IMaterial>
  public native let scale: ref<IEvaluatorVector>;
  public native let emissiveScale: ref<IEvaluatorVector>;
  public native let normalThreshold: Float;
  public native let horizontalFlip: Bool;
  public native let verticalFlip: Bool;
  public native let fadeOutTime: Float;
  public native let fadeInTime: Float;
  public native let additionalRotation: Float;
  public native let randomRotation: Bool;
  public native let randomAtlasing: Bool;
  public native let isStretchEnabled: Bool;
  public native let isAttached: Bool;
  public native let normalsBlendingMode: RenderDecalNormalsBlendingMode;
  public native let atlasFrameStart: Int32;
  public native let atlasFrameEnd: Int32;
  public native let orderPriority: RenderDecalOrderPriority;
  public native let surfaceType: ERenderObjectType;
  public native let decalRenderMode: EDecalRenderMode;
}
