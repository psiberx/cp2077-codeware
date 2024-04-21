public native struct rendRenderMeshBlobHeader {
  native let version: Uint32;
  native let dataProcessing: Uint32;
  native let bonePositions: array<Vector4>;
  native let renderLODs: array<Float>;
  native let renderChunks: array<Uint8>;
  native let renderChunkInfos: array<rendChunk>;
  native let speedTreeWind: array<Uint8>;
  native let opacityMicromaps: array<Uint8>;
  native let customData: array<Uint8>;
  native let customDataElemStride: Uint32;
  native let topologyData: array<Uint8>;
  native let topologyDataStride: Uint32;
  native let topologyMetadata: array<Uint8>;
  native let topologyMetadataStride: Uint32;
  native let topology: array<rendTopologyData>;
  native let quantizationScale: Vector4;
  native let quantizationOffset: Vector4;
  native let vertexBufferSize: Uint32;
  native let indexBufferSize: Uint32;
  native let indexBufferOffset: Uint32;
}
