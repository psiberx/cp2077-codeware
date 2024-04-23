public native class animAnimation extends ISerializable {
  native let tags: redTagList;
  native let name: CName;
  native let duration: Float;
  native let animationType: animAnimationType;
  native let animBuffer: ref<animIAnimationBuffer>;
  native let additionalTransforms: animAdditionalTransformContainer;
  native let additionalTracks: animAdditionalFloatTrackContainer;
  native let motionExtraction: ref<animIMotionExtraction>;
  native let frameClamping: Bool;
  native let frameClampingStartFrame: Int8;
  native let frameClampingEndFrame: Int8;
}
