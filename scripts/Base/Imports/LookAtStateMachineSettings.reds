public native struct LookAtStateMachineSettings {
  native let partName: CName;
  native let partAlias: CName;
  native let sphereAttachmentBone: CName;
  native let sphereRadius: Float;
  native let followingSpeedFactor: Float;
  native let enableFloatTrack: CName;
  native let eyesOverrideFloatTrack: CName;
  native let transitionSpeedMultiplier: Float;
  native let blendWeightPowFactor: Float;
  native let coneLimitReached: CName;
  native let allowToBlendBehindBack: Bool;
}
