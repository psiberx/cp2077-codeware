public native class animAnimNode_StaticSwitch extends animAnimNode_MotionTableSwitch {
  native let condition: ref<animIStaticCondition>;
  native let motionProvider: ref<animIMotionTableProvider>;
  native let True: animPoseLink;
  native let False: animPoseLink;
}
