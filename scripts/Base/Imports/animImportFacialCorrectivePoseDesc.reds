public native struct animImportFacialCorrectivePoseDesc {
  native let influencedBy: array<CName>;
  native let influenceMainWeightIndices: array<Uint16>;
  native let poses: array<animImportFacialCorrectivePoseDataDesc>;
  native let parentsInBetweenIndices: array<Int16>;
  native let parentIndices: array<Uint16>;
  native let name: CName;
  native let index: Uint16;
  native let influencedBySpeed: Uint8;
  native let poseType: Uint8;
  native let poseLOD: Uint8;
  native let weights: array<Float>;
  native let inBetweenScopeMultipliers: array<Float>;
  native let linearCorrection: Bool;
  native let useGlobalWeight: Bool;
}
