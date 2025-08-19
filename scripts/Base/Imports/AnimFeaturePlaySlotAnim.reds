public native class AnimFeaturePlaySlotAnim extends AnimFeature {
  public native let slotName: CName;
  public native let animationName: CName;
  public native let blendInTime: Float;
  public native let blendOutTime: Float;
  public native let speedMultiplier: Float;
  public native let startOffsetRelative: Float;
  public native let playAsAdditive: Bool;
  public native let enableMotion: Bool;
  public native let numberOfLoops: Int32;

  public final native func SetSlotName()
}
