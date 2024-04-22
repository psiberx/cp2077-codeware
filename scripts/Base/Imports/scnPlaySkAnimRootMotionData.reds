public native struct scnPlaySkAnimRootMotionData {
  native let enabled: Bool;
  native let placementMode: scnRootMotionAnimPlacementMode;
  native let originMarker: scnMarker;
  native let originOffset: Transform;
  native let customBlendInTime: Float;
  native let customBlendInCurve: scnEasingType;
  native let removePitchRollRotation: Bool;
  native let meshDissolvingEnabled: Bool;
  native let snapToGroundStart: Float;
  native let snapToGroundEnd: Float;
  native let snapToGround: Bool;
  native let vehicleChangePhysicsState: Bool;
  native let vehicleEnabledPhysicsOnEnd: Bool;
  native let trajectoryLOD: array<scnAnimationMotionSample>;
}
