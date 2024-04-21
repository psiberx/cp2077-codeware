public native struct questUseWorkspotPlayerParams {
  native persistent let tier: questUseWorkspotTier;
  native persistent let cameraSettings: Tier3CameraSettings;
  native persistent let emptyHands: Bool;
  native persistent let cameraUseTrajectorySpace: Bool;
  native persistent let applyCameraParams: Bool;
  native persistent let vehicleProceduralCameraWeight: Float;
  native persistent let parallaxWeight: Float;
  native persistent let parallaxSpace: questCameraParallaxSpace;
}
