public native class animAnimNode_TransformRotator extends animAnimNode_OnePoseInput {
  native let transform: animTransformIndex;
  native let axis: Vector3;
  native let valueScale: Float;
  native let clamp: Bool;
  native let angleMin: Float;
  native let angleMax: Float;
  native let angleValueNode: animFloatLink;
  native let angleSpeedNode: animFloatLink;
}
