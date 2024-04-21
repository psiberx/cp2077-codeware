public native class effectTrackItemDecal extends effectTrackItem {
  native let material: ResourceRef; // rRef<IMaterial>
  native let normalThreshold: Float;
  native let horizontalFlip: Bool;
  native let verticalFlip: Bool;
  native let fadeOutTime: Float;
  native let fadeInTime: Float;
  native let additionalRotation: Float;
  native let randomRotation: Bool;
  native let randomAtlasing: Bool;
  native let isStretchEnabled: Bool;
  native let isAttached: Bool;
  native let normalsBlendingMode: RenderDecalNormalsBlendingMode;
  native let atlasFrameStart: Int32;
  native let atlasFrameEnd: Int32;
  native let orderPriority: RenderDecalOrderPriority;
  native let surfaceType: ERenderObjectType;
  native let decalRenderMode: EDecalRenderMode;
}
