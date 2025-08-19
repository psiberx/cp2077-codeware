public native class animAnimNode_StackTransformsExtender extends animAnimNode_OnePoseInput {
  public native let tag: CName;
  public native let transformInfos: array<animTransformInfo>;
  public native let snapMethods: array<animStackTransformsExtender_SnapToBoneMethod>;
  public native let snapToReferenceValues: array<Bool>;
  public native let snapTargetBones: array<animTransformIndex>;
  public native let offsetToReferenceValues: array<Bool>;
  public native let offsetSpaceBones: array<animTransformIndex>;
  public native let offsets: array<QsTransform>;
}
