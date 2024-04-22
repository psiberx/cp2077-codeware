public native struct animImportFacialSetupCombinedDesc {
  native let face: animImportFacialSetupDesc;
  native let eyes: animImportFacialSetupDesc;
  native let tongue: animImportFacialSetupDesc;
  native let usedTransformIndices: array<Uint16>;
  native let lipsyncOverrideToMainPosesTracksMapping: array<Int16>;
  native let firstLipsyncOverrideTrackIndex: Int16;
}
