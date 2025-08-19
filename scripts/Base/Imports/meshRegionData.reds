public native struct meshRegionData {
  public native let chunkDataIntact: array<meshChunkOffset>;
  public native let chunkDataFractured: array<meshChunkOffset>;
  public native let chunkMaskIntact: Uint64;
  public native let chunkMaskFractured: Uint64;
  public native let isStaticRemains: Bool;
}
