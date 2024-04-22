public native struct animSetBoneTransform_JsonEntry {
  native let transformToChange: CName;
  native let setMethod: animSetBoneTransformEntry_SetMethod;
  native let snapToReference: Bool;
  native let sourceBone: CName;
  native let offsetToReference: Bool;
  native let offsetSpaceBone: CName;
  native let offset: QsTransform;
}
