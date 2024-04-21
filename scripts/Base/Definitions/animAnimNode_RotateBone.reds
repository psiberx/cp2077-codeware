public native class animAnimNode_RotateBone extends animAnimNode_Base {
  native let inputNode: animPoseLink;
  native let angleNode: animFloatLink;
  native let minValueNode: animFloatLink;
  native let maxValueNode: animFloatLink;
  native let bone: animTransformIndex;
  native let axis: animETransformAxis;
  native let scale: Float;
  native let biasAngle: Float;
  native let minAngle: Float;
  native let maxAngle: Float;
  native let clampRotation: Bool;
  native let useIncrementalMode: Bool;
  native let resetOnActivation: Bool;
  native let inModelSpace: Bool;
}
