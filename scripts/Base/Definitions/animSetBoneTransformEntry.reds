public native struct animSetBoneTransformEntry {
  native let transformToChange: animTransformIndex;
  native let setMethod: animSetBoneTransformEntry_SetMethod;
  native let snapToReference: Bool;
  native let sourceBone: animTransformIndex;
  native let offsetToReference: Bool;
  native let offsetSpaceBone: animTransformIndex;
  native let offset: QsTransform;
}
