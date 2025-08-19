public native class meshMeshParamCloth extends meshMeshParameter {
  public native let lodChunkIndices: array<array<Uint16>>;
  public native let chunks: array<meshPhxClothChunkData>;
  public native let drivers: array<array<Uint16>>;
  public native let capsules: ref<physicsclothClothCapsuleExportData>;
}
