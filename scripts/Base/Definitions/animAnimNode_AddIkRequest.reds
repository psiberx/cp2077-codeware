public native class animAnimNode_AddIkRequest extends animAnimNode_OnePoseInput {
  native let ikChain: CName;
  native let targetBone: animTransformIndex;
  native let positionOffset: Vector3;
  native let rotationOffset: Quaternion;
  native let poleVector: animPoleVectorDetails;
  native let weightPosition: Float;
  native let weightRotation: Float;
  native let blendTimeIn: Float;
  native let blendTimeOut: Float;
  native let priority: Int32;
}
