public native class animAnimNode_AimConstraint extends animAnimNode_OnePoseInput {
  public native let areSourceChannelsResaved: Bool;
  public native let targetTransforms: array<ref<animAnimNodeSourceChannel_WeightedVector>>;
  public native let targetTransform: animTransformIndex;
  public native let upTransform: ref<animIAnimNodeSourceChannel_Vector>;
  public native let transformIndex: animTransformIndex;
  public native let forwardAxisLS: Vector3;
  public native let upAxisLS: Vector3;
  public native let weightMode: animConstraintWeightMode;
  public native let weight: Float;
  public native let weightFloatTrack: animNamedTrackIndex;
}
