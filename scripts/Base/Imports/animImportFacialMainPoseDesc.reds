public native struct animImportFacialMainPoseDesc {
  public native let influencedBy: array<CName>;
  public native let influenceMainWeightIndices: array<Uint16>;
  public native let poses: array<animImportFacialPoseDesc>;
  public native let poseIndices: array<Uint16>;
  public native let weights: array<Float>;
  public native let inBetweenScopeMultipliers: array<Float>;
  public native let name: CName;
  public native let index: Uint16;
  public native let influenceType: Uint8;
  public native let side: Uint8;
  public native let facePart: Uint8;
}
