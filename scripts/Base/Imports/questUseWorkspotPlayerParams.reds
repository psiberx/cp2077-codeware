public native struct questUseWorkspotPlayerParams {
  public native persistent let tier: questUseWorkspotTier;
  public native persistent let cameraSettings: Tier3CameraSettings;
  public native persistent let emptyHands: Bool;
  public native persistent let cameraUseTrajectorySpace: Bool;
  public native persistent let applyCameraParams: Bool;
  public native persistent let vehicleProceduralCameraWeight: Float;
  public native persistent let parallaxWeight: Float;
  public native persistent let parallaxSpace: questCameraParallaxSpace;
}
