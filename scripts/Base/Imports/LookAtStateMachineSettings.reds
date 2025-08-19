public native struct LookAtStateMachineSettings {
  public native let partName: CName;
  public native let partAlias: CName;
  public native let sphereAttachmentBone: CName;
  public native let sphereRadius: Float;
  public native let followingSpeedFactor: Float;
  public native let followingSpeedByAngleCurve: CurveDataFloat;
  public native let enableFloatTrack: CName;
  public native let eyesOverrideFloatTrack: CName;
  public native let transitionSpeedMultiplier: Float;
  public native let blendWeightPowFactor: Float;
  public native let coneLimitReached: CName;
  public native let allowToBlendBehindBack: Bool;
}
