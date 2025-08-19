public native class animAnimNode_Ik2 extends animAnimNode_Base {
  public native let firstBone: animTransformIndex;
  public native let secondBone: animTransformIndex;
  public native let endBone: animTransformIndex;
  public native let hingeAxis: animAxis;
  public native let minHingeAngleDegrees: Float;
  public native let maxHingeAngleDegrees: Float;
  public native let firstBoneIkGain: Float;
  public native let secondBoneIkGain: Float;
  public native let endBoneIkGain: Float;
  public native let enforceEndPosition: Bool;
  public native let enforceEndOrientation: Bool;
  public native let endBoneOffsetPositionLS: Vector4;
  public native let bone: animTransformIndex;
  public native let floatTrack: animNamedTrackIndex;
  public native let inputPoseNode: animPoseLink;
  public native let weightNode: animFloatLink;
  public native let endTargetPositionNode: animVectorLink;
  public native let endTargetOrientationNode: animQuaternionLink;
}
