public native struct animImportFacialCorrectivePoseDesc {
  public native let influencedBy: array<CName>;
  public native let influenceMainWeightIndices: array<Uint16>;
  public native let poses: array<animImportFacialCorrectivePoseDataDesc>;
  public native let parentsInBetweenIndices: array<Int16>;
  public native let parentIndices: array<Uint16>;
  public native let name: CName;
  public native let index: Uint16;
  public native let influencedBySpeed: Uint8;
  public native let poseType: Uint8;
  public native let poseLOD: Uint8;
  public native let weights: array<Float>;
  public native let inBetweenScopeMultipliers: array<Float>;
  public native let linearCorrection: Bool;
  public native let useGlobalWeight: Bool;
}
