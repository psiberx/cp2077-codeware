public native class animAnimNode_AimConstraint extends animAnimNode_OnePoseInput {
  native let areSourceChannelsResaved: Bool;
  native let targetTransforms: array<ref<animAnimNodeSourceChannel_WeightedVector>>;
  native let targetTransform: animTransformIndex;
  native let upTransform: ref<animIAnimNodeSourceChannel_Vector>;
  native let transformIndex: animTransformIndex;
  native let forwardAxisLS: Vector3;
  native let upAxisLS: Vector3;
  native let weightMode: animConstraintWeightMode;
  native let weight: Float;
  native let weightFloatTrack: animNamedTrackIndex;
}
