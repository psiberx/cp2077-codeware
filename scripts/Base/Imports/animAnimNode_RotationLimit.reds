public native class animAnimNode_RotationLimit extends animAnimNode_OnePoseInput {
  native let constrainedTransform: animTransformIndex;
  native let limitOnX: animSmoothFloatClamp;
  native let limitOnY: animSmoothFloatClamp;
  native let limitOnZ: animSmoothFloatClamp;
  native let useEyesLookAtBlendWeight: Bool;
  native let weightLink: animFloatLink;
}
