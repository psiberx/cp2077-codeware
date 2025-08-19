public native struct animImportFacialSetupCombinedDesc {
  public native let face: animImportFacialSetupDesc;
  public native let eyes: animImportFacialSetupDesc;
  public native let tongue: animImportFacialSetupDesc;
  public native let usedTransformIndices: array<Uint16>;
  public native let lipsyncOverrideToMainPosesTracksMapping: array<Int16>;
  public native let firstLipsyncOverrideTrackIndex: Int16;
}
