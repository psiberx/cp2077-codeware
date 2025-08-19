public native class animAnimation extends ISerializable {
  public native let tags: redTagList;
  public native let name: CName;
  public native let duration: Float;
  public native let animationType: animAnimationType;
  public native let animBuffer: ref<animIAnimationBuffer>;
  public native let additionalTransforms: animAdditionalTransformContainer;
  public native let additionalTracks: animAdditionalFloatTrackContainer;
  public native let motionExtraction: ref<animIMotionExtraction>;
  public native let frameClamping: Bool;
  public native let frameClampingStartFrame: Int8;
  public native let frameClampingEndFrame: Int8;
}
