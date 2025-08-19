public native struct scnPlaySkAnimRootMotionData {
  public native let enabled: Bool;
  public native let placementMode: scnRootMotionAnimPlacementMode;
  public native let originMarker: scnMarker;
  public native let originOffset: Transform;
  public native let customBlendInTime: Float;
  public native let customBlendInCurve: scnEasingType;
  public native let removePitchRollRotation: Bool;
  public native let meshDissolvingEnabled: Bool;
  public native let snapToGroundStart: Float;
  public native let snapToGroundEnd: Float;
  public native let snapToGround: Bool;
  public native let vehicleChangePhysicsState: Bool;
  public native let vehicleEnabledPhysicsOnEnd: Bool;
  public native let trajectoryLOD: array<scnAnimationMotionSample>;
}
