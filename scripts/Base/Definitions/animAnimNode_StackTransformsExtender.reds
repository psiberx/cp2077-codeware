public native class animAnimNode_StackTransformsExtender extends animAnimNode_OnePoseInput {
  native let tag: CName;
  native let transformInfos: array<animTransformInfo>;
  native let snapMethods: array<animStackTransformsExtender_SnapToBoneMethod>;
  native let snapToReferenceValues: array<Bool>;
  native let snapTargetBones: array<animTransformIndex>;
  native let offsetToReferenceValues: array<Bool>;
  native let offsetSpaceBones: array<animTransformIndex>;
  native let offsets: array<QsTransform>;
}
