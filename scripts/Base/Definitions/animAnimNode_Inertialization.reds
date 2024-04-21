public native class animAnimNode_Inertialization extends animAnimNode_OnePoseInput {
  native let safeMode: Bool;
  native let transformsCountUpperBound: Uint32;
  native let tracksCountUpperBound: Uint32;
  native let rotationLimits: array<animInertializationRotationLimit>;
}
