public native struct SMeshChunkPacked {
  public native let vertexType: EMeshVertexType;
  public native let materialID: array<CName>;
  public native let numBonesPerVertex: Uint8;
  public native let numVertices: Uint32;
  public native let numIndices: Uint32;
  public native let firstVertex: Uint32;
  public native let firstIndex: Uint32;
  public native let useForShadowmesh: Bool;
  public native let streams: array<SMeshStream>;
  public native let streamMask: Uint64;
  public native let lodMask: Uint8;
}
