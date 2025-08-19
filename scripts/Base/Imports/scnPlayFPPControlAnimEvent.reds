public native class scnPlayFPPControlAnimEvent extends scnPlayAnimEvent {
  public native let gameplayAnimName: ref<scnAnimName>;
  public native let FPPControlActive: Bool;
  public native let blendOverride: scnfppBlendOverride;
  public native let cameraUseTrajectorySpace: Bool;
  public native let cameraBlendInDuration: Float;
  public native let cameraBlendOutDuration: Float;
  public native let stayInScene: Bool;
  public native let idleIsMountedWorkspot: Bool;
  public native let enableWorldSpaceSmoothing: Bool;
  public native let isSceneCarrying: Bool;
  public native let cameraParallaxWeight: Float;
  public native let cameraParallaxSpace: scnfppParallaxSpace;
  public native let vehicleProceduralCameraWeight: Float;
  public native let yawLimitLeft: Float;
  public native let yawLimitRight: Float;
  public native let pitchLimitTop: Float;
  public native let pitchLimitBottom: Float;
  public native let genderSpecificParams: array<scnfppGenderSpecificParams>;
}
