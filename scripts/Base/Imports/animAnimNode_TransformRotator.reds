public native class animAnimNode_TransformRotator extends animAnimNode_OnePoseInput {
  public native let transform: animTransformIndex;
  public native let axis: Vector3;
  public native let valueScale: Float;
  public native let clamp: Bool;
  public native let angleMin: Float;
  public native let angleMax: Float;
  public native let angleValueNode: animFloatLink;
  public native let angleSpeedNode: animFloatLink;
}
