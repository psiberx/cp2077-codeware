public native struct animImportFacialPoseDesc {
  native let transforms: array<animImportFacialTransform>;
  native let transformsNoScale: array<animImportFacialTransformNoScale>;
  native let transformIds: array<Uint16>;
  native let transformNames: array<CName>;
}
