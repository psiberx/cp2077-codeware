public native class animAnimNode_AddIkRequest extends animAnimNode_OnePoseInput {
  public native let ikChain: CName;
  public native let targetBone: animTransformIndex;
  public native let positionOffset: Vector3;
  public native let rotationOffset: Quaternion;
  public native let poleVector: animPoleVectorDetails;
  public native let weightPosition: Float;
  public native let weightRotation: Float;
  public native let blendTimeIn: Float;
  public native let blendTimeOut: Float;
  public native let priority: Int32;
}
