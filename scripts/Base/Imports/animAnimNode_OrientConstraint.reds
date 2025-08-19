public native class animAnimNode_OrientConstraint extends animAnimNode_OnePoseInput {
  public native let areSourceChannelsResaved: Bool;
  public native let inputTransforms: array<ref<animAnimNodeSourceChannel_WeightedQuat>>;
  public native let preprocessedWeights: array<Float>;
  public native let inputWeightedTransforms: array<animAnimNode_OrientConstraint_WeightedTransform>;
  public native let transformIndex: animTransformIndex;
  public native let weightMode: animConstraintWeightMode;
  public native let weight: Float;
  public native let weightFloatTrack: animNamedTrackIndex;
}
