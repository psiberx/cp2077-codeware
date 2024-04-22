public native class animAnimNode_RotateBoneByQuaternion extends animAnimNode_Base {
  native let inputNode: animPoseLink;
  native let quaternionNode: animQuaternionLink;
  native let bone: animTransformIndex;
  native let useIncrementalMode: Bool;
  native let resetOnActivation: Bool;
}
