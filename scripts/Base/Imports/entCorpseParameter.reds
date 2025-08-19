public native class entCorpseParameter extends entEntityParameter {
  public native let lod: Uint32;
  public native let bakedPose: array<QsTransform>;
  public native let bakedBoneNames: array<CName>;
  public native let forceLOD0Components: array<CRUID>;
  public native let baseRig: ResourceAsyncRef; // raRef<animRig>
}
