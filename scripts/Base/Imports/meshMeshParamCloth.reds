public native class meshMeshParamCloth extends meshMeshParameter {
  native let lodChunkIndices: array<array<Uint16>>;
  native let chunks: array<meshPhxClothChunkData>;
  native let drivers: array<array<Uint16>>;
  native let capsules: ref<physicsclothClothCapsuleExportData>;
}
