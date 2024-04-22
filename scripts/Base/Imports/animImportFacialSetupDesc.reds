public native struct animImportFacialSetupDesc {
  native let initialPose: array<animImportFacialInitialPoseEntryDesc>;
  native let initialControls: animImportFacialInitialControlsDesc;
  native let mainPoses: array<animImportFacialMainPoseDesc>;
  native let mainPosesInfo: array<animSermoPoseInfo>;
  native let jawAreaTrackIndices: array<Int16>;
  native let lipsAreaTrackIndices: array<Int16>;
  native let eyesAreaTrackIndices: array<Int16>;
  native let numCachedPoseTracks: Uint16;
  native let correctivePoses: array<animImportFacialCorrectivePoseDesc>;
  native let globalPoseLimits: array<animPoseLimitWeights>;
  native let wrinkleStartingIndex: Uint16;
  native let wrinkleMapping: array<Uint16>;
}
