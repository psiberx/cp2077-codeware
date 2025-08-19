public native class animAnimNode_StaticSwitch extends animAnimNode_MotionTableSwitch {
  public native let condition: ref<animIStaticCondition>;
  public native let motionProvider: ref<animIMotionTableProvider>;
  public native let True: animPoseLink;
  public native let False: animPoseLink;
}
