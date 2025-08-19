public native struct animImportFacialSetupDesc {
  public native let initialPose: array<animImportFacialInitialPoseEntryDesc>;
  public native let initialControls: animImportFacialInitialControlsDesc;
  public native let mainPoses: array<animImportFacialMainPoseDesc>;
  public native let mainPosesInfo: array<animSermoPoseInfo>;
  public native let jawAreaTrackIndices: array<Int16>;
  public native let lipsAreaTrackIndices: array<Int16>;
  public native let eyesAreaTrackIndices: array<Int16>;
  public native let numCachedPoseTracks: Uint16;
  public native let correctivePoses: array<animImportFacialCorrectivePoseDesc>;
  public native let globalPoseLimits: array<animPoseLimitWeights>;
  public native let wrinkleStartingIndex: Uint16;
  public native let wrinkleMapping: array<Uint16>;
}
