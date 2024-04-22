public native struct meshRegionData {
  native let chunkDataIntact: array<meshChunkOffset>;
  native let chunkDataFractured: array<meshChunkOffset>;
  native let chunkMaskIntact: Uint64;
  native let chunkMaskFractured: Uint64;
  native let isStaticRemains: Bool;
}
