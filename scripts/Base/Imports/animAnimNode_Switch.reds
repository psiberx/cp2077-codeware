public native class animAnimNode_Switch extends animAnimNode_MotionTableSwitch {
  native let numInputs: Uint32;
  native let blendTime: Float;
  native let timeWarpingEnabled: Bool;
  native let weightNode: animFloatLink;
  native let inputNodes: array<animPoseLink>;
  native let pushDataByTag: CName;
  native let canRequestInertialization: Bool;
}
