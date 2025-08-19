public native struct rendChunk {
  public native let chunkVertices: rendVertexBufferChunk;
  public native let chunkIndices: rendIndexBufferChunk;
  public native let numVertices: Uint16;
  public native let numIndices: Uint32;
  public native let materialId: array<CName>;
  public native let vertexFactory: Uint8;
  public native let baseRenderMask: Uint16;
  public native let mergedRenderMask: Uint16;
  public native let lodMask: Uint8;
}
