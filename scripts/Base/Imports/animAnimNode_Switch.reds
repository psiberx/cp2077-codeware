public native class animAnimNode_Switch extends animAnimNode_MotionTableSwitch {
  public native let numInputs: Uint32;
  public native let blendTime: Float;
  public native let timeWarpingEnabled: Bool;
  public native let syncMethod: ref<animISyncMethod>;
  public native let motionProvider: ref<animIMotionTableProvider>;
  public native let weightNode: animFloatLink;
  public native let inputNodes: array<animPoseLink>;
  public native let pushDataByTag: CName;
  public native let canRequestInertialization: Bool;
}
