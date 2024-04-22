public native class animAnimNode_Ik2 extends animAnimNode_Base {
  native let firstBone: animTransformIndex;
  native let secondBone: animTransformIndex;
  native let endBone: animTransformIndex;
  native let hingeAxis: animAxis;
  native let minHingeAngleDegrees: Float;
  native let maxHingeAngleDegrees: Float;
  native let firstBoneIkGain: Float;
  native let secondBoneIkGain: Float;
  native let endBoneIkGain: Float;
  native let enforceEndPosition: Bool;
  native let enforceEndOrientation: Bool;
  native let endBoneOffsetPositionLS: Vector4;
  native let bone: animTransformIndex;
  native let floatTrack: animNamedTrackIndex;
  native let inputPoseNode: animPoseLink;
  native let weightNode: animFloatLink;
  native let endTargetPositionNode: animVectorLink;
  native let endTargetOrientationNode: animQuaternionLink;
}
