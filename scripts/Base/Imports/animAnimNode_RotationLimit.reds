public native class animAnimNode_RotationLimit extends animAnimNode_OnePoseInput {
  public native let constrainedTransform: animTransformIndex;
  public native let limitOnX: animSmoothFloatClamp;
  public native let limitOnY: animSmoothFloatClamp;
  public native let limitOnZ: animSmoothFloatClamp;
  public native let useEyesLookAtBlendWeight: Bool;
  public native let weightLink: animFloatLink;
}
