public native class animAnimNode_TriggerBranch extends animAnimNode_Base {
  native let base: animPoseLink;
  native let overlay: animPoseLink;
  native let blendIn: Float;
  native let blendOut: Float;
  native let startEvent: CName;
  native let endEvent: CName;
  native let cooldown: Float;
}
