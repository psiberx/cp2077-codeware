public native struct scnfppGenderSpecificParams {
  public native let genderMask: scnGenderMask;
  public native let transitionBlendInTrajectorySpaceAngles: array<EulerAngles>;
  public native let transitionBlendInCameraSpace: array<Float>;
  public native let transitionEndInputAngles: array<EulerAngles>;
  public native let idleCameraLs: EulerAngles;
  public native let idleControlCameraMs: EulerAngles;
}
