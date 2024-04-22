public native struct rendChunk {
  native let chunkVertices: rendVertexBufferChunk;
  native let chunkIndices: rendIndexBufferChunk;
  native let numVertices: Uint16;
  native let numIndices: Uint32;
  native let materialId: array<CName>;
  native let vertexFactory: Uint8;
  native let baseRenderMask: Uint16;
  native let mergedRenderMask: Uint16;
  native let lodMask: Uint8;
}
