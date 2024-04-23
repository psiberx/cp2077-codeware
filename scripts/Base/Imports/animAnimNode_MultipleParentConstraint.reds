public native class animAnimNode_MultipleParentConstraint extends animAnimNode_OnePoseInput {
  native let parentsTransform: array<ref<animIAnimNodeSourceChannel_QsTransform>>;
  native let parentsWeight: array<ref<animIAnimNodeSourceChannel_Float>>;
  native let areSourceChannelsResaved: Bool;
  native let parentsTransforms: array<animAnimNode_MultipleParentConstraint_ParentInfo>;
  native let transformIndex: animTransformIndex;
  native let interpolationType: animEInterpolationType;
  native let weightMode: animConstraintWeightMode;
  native let weight: Float;
  native let weightFloatTrack: animNamedTrackIndex;
}
