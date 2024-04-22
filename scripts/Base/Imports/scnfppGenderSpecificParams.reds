public native struct scnfppGenderSpecificParams {
  native let genderMask: scnGenderMask;
  native let transitionBlendInTrajectorySpaceAngles: array<EulerAngles>;
  native let transitionBlendInCameraSpace: array<Float>;
  native let transitionEndInputAngles: array<EulerAngles>;
  native let idleCameraLs: EulerAngles;
  native let idleControlCameraMs: EulerAngles;
}
