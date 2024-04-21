public native class animAnimNode_TranslateBone extends animAnimNode_Base {
  native let inputNode: animPoseLink;
  native let inputTranslation: animVectorLink;
  native let scale: Vector4;
  native let biasValue: Vector4;
  native let bone: animTransformIndex;
  native let useIncrementalMode: Bool;
  native let resetOnActivation: Bool;
}
