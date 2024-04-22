public native struct SMeshChunkPacked {
  native let vertexType: EMeshVertexType;
  native let materialID: array<CName>;
  native let numBonesPerVertex: Uint8;
  native let numVertices: Uint32;
  native let numIndices: Uint32;
  native let firstVertex: Uint32;
  native let firstIndex: Uint32;
  native let useForShadowmesh: Bool;
  native let streams: array<SMeshStream>;
  native let streamMask: Uint64;
  native let lodMask: Uint8;
}
