public native class animAnimNode_BlendMultiple extends animAnimNode_Base {
  public native let inputValues: array<Float>;
  public native let sortedInputValues: array<Float>;
  public native let minWeight: Float;
  public native let maxWeight: Float;
  public native let radialBlending: Bool;
  public native let timeWarpingEnabled: Bool;
  public native let syncMethod: ref<animISyncMethod>;
  public native let motionProvider: ref<animIMotionTableProvider>;
  public native let weightNode: animFloatLink;
  public native let inputNodes: array<animPoseLink>;
}
