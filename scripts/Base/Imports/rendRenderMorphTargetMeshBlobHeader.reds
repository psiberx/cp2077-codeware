public native struct rendRenderMorphTargetMeshBlobHeader {
  native let version: Uint32;
  native let numDiffs: Uint32;
  native let numDiffsMapping: Uint32;
  native let numTargets: Uint32;
  native let targetStartsInVertexDiffs: array<Uint32>;
  native let targetStartsInVertexDiffsMapping: array<Uint32>;
  native let targetPositionDiffScale: array<Vector4>;
  native let targetPositionDiffOffset: array<Vector4>;
  native let numVertexDiffsInEachChunk: array<array<Uint32>>;
  native let numVertexDiffsMappingInEachChunk: array<array<Uint32>>;
  native let targetTextureDiffsData: array<rendRenderMorphTargetMeshBlobTextureData>;
}
