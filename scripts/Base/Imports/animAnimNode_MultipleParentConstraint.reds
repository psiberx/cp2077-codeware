public native class animAnimNode_MultipleParentConstraint extends animAnimNode_OnePoseInput {
  public native let parentsTransform: array<ref<animIAnimNodeSourceChannel_QsTransform>>;
  public native let parentsWeight: array<ref<animIAnimNodeSourceChannel_Float>>;
  public native let areSourceChannelsResaved: Bool;
  public native let parentsTransforms: array<animAnimNode_MultipleParentConstraint_ParentInfo>;
  public native let transformIndex: animTransformIndex;
  public native let interpolationType: animEInterpolationType;
  public native let weightMode: animConstraintWeightMode;
  public native let weight: Float;
  public native let weightFloatTrack: animNamedTrackIndex;
}
