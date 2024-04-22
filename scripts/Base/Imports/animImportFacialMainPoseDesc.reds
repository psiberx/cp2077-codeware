public native struct animImportFacialMainPoseDesc {
  native let influencedBy: array<CName>;
  native let influenceMainWeightIndices: array<Uint16>;
  native let poses: array<animImportFacialPoseDesc>;
  native let poseIndices: array<Uint16>;
  native let weights: array<Float>;
  native let inBetweenScopeMultipliers: array<Float>;
  native let name: CName;
  native let index: Uint16;
  native let influenceType: Uint8;
  native let side: Uint8;
  native let facePart: Uint8;
}
