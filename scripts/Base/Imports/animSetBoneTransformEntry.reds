public native struct animSetBoneTransformEntry {
  public native let transformToChange: animTransformIndex;
  public native let setMethod: animSetBoneTransformEntry_SetMethod;
  public native let snapToReference: Bool;
  public native let sourceBone: animTransformIndex;
  public native let offsetToReference: Bool;
  public native let offsetSpaceBone: animTransformIndex;
  public native let offset: QsTransform;
}
