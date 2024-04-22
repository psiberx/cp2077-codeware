public native struct animAnimNode_MultipleParentConstraint_ParentInfo {
  native let parentTransform: animTransformIndex;
  native let parentWeightMode: animConstraintWeightMode;
  native let parentStaticWeight: Float;
  native let parentTrackWeight: animNamedTrackIndex;
  native let useComplementWeight: Bool;
  native let useOffset: Bool;
  native let offset: QsTransform;
}
