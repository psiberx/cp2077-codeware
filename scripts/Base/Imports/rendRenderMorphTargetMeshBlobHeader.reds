public native struct rendRenderMorphTargetMeshBlobHeader {
  public native let version: Uint32;
  public native let numDiffs: Uint32;
  public native let numDiffsMapping: Uint32;
  public native let numTargets: Uint32;
  public native let targetStartsInVertexDiffs: array<Uint32>;
  public native let targetStartsInVertexDiffsMapping: array<Uint32>;
  public native let targetPositionDiffScale: array<Vector4>;
  public native let targetPositionDiffOffset: array<Vector4>;
  public native let numVertexDiffsInEachChunk: array<array<Uint32>>;
  public native let numVertexDiffsMappingInEachChunk: array<array<Uint32>>;
  public native let targetTextureDiffsData: array<rendRenderMorphTargetMeshBlobTextureData>;
}
