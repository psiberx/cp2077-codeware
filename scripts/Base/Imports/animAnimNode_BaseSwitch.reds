public native class animAnimNode_BaseSwitch extends animAnimNode_Base {
  native let blendTime: Float;
  native let timeWarpingEnabled: Bool;
  native let syncMethod: ref<animISyncMethod>;
  native let inputNodes: array<animPoseLink>;
  native let canRequestInertialization: Bool;
}
