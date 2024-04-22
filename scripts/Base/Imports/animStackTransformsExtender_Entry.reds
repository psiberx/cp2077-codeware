public native struct animStackTransformsExtender_Entry {
  native let transformInfo: animTransformInfo;
  native let snapMethod: animStackTransformsExtender_SnapToBoneMethod;
  native let snapToReference: Bool;
  native let snapTargetBone: animTransformIndex;
  native let offsetToReference: Bool;
  native let offsetSpaceBone: animTransformIndex;
  native let offset: QsTransform;
}
