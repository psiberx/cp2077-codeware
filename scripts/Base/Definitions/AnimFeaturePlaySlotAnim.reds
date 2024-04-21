public native class AnimFeaturePlaySlotAnim extends AnimFeature {
  native let slotName: CName;
  native let animationName: CName;
  native let blendInTime: Float;
  native let blendOutTime: Float;
  native let speedMultiplier: Float;
  native let startOffsetRelative: Float;
  native let playAsAdditive: Bool;
  native let enableMotion: Bool;
  native let numberOfLoops: Int32;

  public final native func SetSlotName()
}
