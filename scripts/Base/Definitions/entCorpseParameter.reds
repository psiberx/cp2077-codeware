public native class entCorpseParameter extends entEntityParameter {
  native let lod: Uint32;
  native let bakedPose: array<QsTransform>;
  native let bakedBoneNames: array<CName>;
  native let forceLOD0Components: array<CRUID>;
  native let baseRig: ResourceAsyncRef; // raRef<animRig>
}
