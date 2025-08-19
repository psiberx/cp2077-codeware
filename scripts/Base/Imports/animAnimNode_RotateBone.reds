public native class animAnimNode_RotateBone extends animAnimNode_Base {
  public native let inputNode: animPoseLink;
  public native let angleNode: animFloatLink;
  public native let minValueNode: animFloatLink;
  public native let maxValueNode: animFloatLink;
  public native let bone: animTransformIndex;
  public native let axis: animETransformAxis;
  public native let scale: Float;
  public native let biasAngle: Float;
  public native let minAngle: Float;
  public native let maxAngle: Float;
  public native let clampRotation: Bool;
  public native let useIncrementalMode: Bool;
  public native let resetOnActivation: Bool;
  public native let inModelSpace: Bool;
}
