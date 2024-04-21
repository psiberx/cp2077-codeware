public native class scnPlayFPPControlAnimEvent extends scnPlayAnimEvent {
  native let FPPControlActive: Bool;
  native let blendOverride: scnfppBlendOverride;
  native let cameraUseTrajectorySpace: Bool;
  native let cameraBlendInDuration: Float;
  native let cameraBlendOutDuration: Float;
  native let stayInScene: Bool;
  native let idleIsMountedWorkspot: Bool;
  native let enableWorldSpaceSmoothing: Bool;
  native let isSceneCarrying: Bool;
  native let cameraParallaxWeight: Float;
  native let cameraParallaxSpace: scnfppParallaxSpace;
  native let vehicleProceduralCameraWeight: Float;
  native let yawLimitLeft: Float;
  native let yawLimitRight: Float;
  native let pitchLimitTop: Float;
  native let pitchLimitBottom: Float;
  native let genderSpecificParams: array<scnfppGenderSpecificParams>;
}
