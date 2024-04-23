public native class animAnimNode_Blend2 extends animAnimNode_Base {
  native let minInputValue: Float;
  native let maxInputValue: Float;
  native let timeWarpingEnabled: Bool;
  native let syncMethod: ref<animISyncMethod>;
  native let firstInputNode: animPoseLink;
  native let secondInputNode: animPoseLink;
  native let weightNode: animFloatLink;
}
