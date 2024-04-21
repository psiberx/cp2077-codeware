public native struct entGarmentParameterComponentData {
  native let componentID: CRUID;
  native let meshGeometryHash: Uint64;
  native let visibleTrangleIndexBufferHash: Uint64;
  native let chunks: array<entGarmentParameterChunkData>;
  native let chunksCount: Uint32;
  native let hideComponent: Bool;
  native let bendPowerMultiplier: Float;
  native let bendPowerOffset: Float;
  native let smoothingStrength: Float;
  native let smoothingThreshold: Float;
  native let smoothingExponent: Float;
  native let smoothNormalsEnabled: Bool;
  native let smoothingNumNeighbours: Uint32;
  native let garmentBorderThreshold: Float;
  native let removeHiddenTriangles: Bool;
  native let disableGarment: Bool;
  native let mergeWithInnerLayer: Bool;
  native let numIndices: Uint32;
  native let numOffsets: Uint32;
}
