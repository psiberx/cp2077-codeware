public native struct animAnimNode_BlendSpace_InternalsBlendSpace {
  native let spaceDimension: Uint32;
  native let coordinatesDescriptions: array<animAnimNode_BlendSpace_InternalsBlendSpaceCoordinateDescription>;
  native let spacePoints: array<animAnimNode_BlendSpace_InternalsBlendSpacePoint>;
  native let boundaryPointsCount: Uint32;
  native let fireAnimEndEvent: Bool;
  native let animEndEventName: CName;
  native let isLooped: Bool;
  native let needsRuntimeTriangulation: Bool;
  native let wasRuntimeTriangulationResaveDone: Bool;
  native let cachedSpacePoints_coordinates: array<Float>;
  native let cachedSpaceSimplexes_pointsIndices: array<Uint32>;
  native let cachedSamplesForGridPoints_simplexIndex: array<Int32>;
  native let cachedSamplesForGridPoints_weightsForPoints: array<Float>;
}
