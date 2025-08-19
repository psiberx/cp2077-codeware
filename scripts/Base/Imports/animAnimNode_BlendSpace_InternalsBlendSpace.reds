public native struct animAnimNode_BlendSpace_InternalsBlendSpace {
  public native let spaceDimension: Uint32;
  public native let coordinatesDescriptions: array<animAnimNode_BlendSpace_InternalsBlendSpaceCoordinateDescription>;
  public native let spacePoints: array<animAnimNode_BlendSpace_InternalsBlendSpacePoint>;
  public native let boundaryPointsCount: Uint32;
  public native let fireAnimEndEvent: Bool;
  public native let animEndEventName: CName;
  public native let isLooped: Bool;
  public native let needsRuntimeTriangulation: Bool;
  public native let wasRuntimeTriangulationResaveDone: Bool;
  public native let cachedSpacePoints_coordinates: array<Float>;
  public native let cachedSpaceSimplexes_pointsIndices: array<Uint32>;
  public native let cachedSamplesForGridPoints_simplexIndex: array<Int32>;
  public native let cachedSamplesForGridPoints_weightsForPoints: array<Float>;
}
