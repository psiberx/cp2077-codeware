public native class animAnimNode_OrientConstraint extends animAnimNode_OnePoseInput {
  native let areSourceChannelsResaved: Bool;
  native let inputTransforms: array<ref<animAnimNodeSourceChannel_WeightedQuat>>;
  native let preprocessedWeights: array<Float>;
  native let inputWeightedTransforms: array<animAnimNode_OrientConstraint_WeightedTransform>;
  native let transformIndex: animTransformIndex;
  native let weightMode: animConstraintWeightMode;
  native let weight: Float;
  native let weightFloatTrack: animNamedTrackIndex;
}
