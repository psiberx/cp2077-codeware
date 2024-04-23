public native class animAnimNode_PointConstraint extends animAnimNode_OnePoseInput {
  native let areSourceChannelsResaved: Bool;
  native let inputTransforms: array<ref<animAnimNodeSourceChannel_WeightedVector>>;
  native let preprocessedWeights: array<Float>;
  native let inputWeightedTransforms: array<animAnimNode_PointConstraint_WeightedTransform>;
  native let transformIndex: animTransformIndex;
  native let weightMode: animConstraintWeightMode;
  native let weight: Float;
  native let weightFloatTrack: animNamedTrackIndex;
}
