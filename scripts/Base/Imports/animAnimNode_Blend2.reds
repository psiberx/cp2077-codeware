public native class animAnimNode_Blend2 extends animAnimNode_Base {
  public native let minInputValue: Float;
  public native let maxInputValue: Float;
  public native let timeWarpingEnabled: Bool;
  public native let syncMethod: ref<animISyncMethod>;
  public native let firstInputNode: animPoseLink;
  public native let secondInputNode: animPoseLink;
  public native let weightNode: animFloatLink;
}
