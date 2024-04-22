public abstract native class IMaterialDefinition extends IMaterial {
  native let canHaveTangentUpdate: Bool;
  native let canHaveDismemberment: Bool;
  native let hasDPL: Bool;
  native let canBeMasked: Bool;
  native let shadingRateMode: EMaterialShadingRateMode;
  native let materialVersion: Uint8;
  native let vertexFactories: array<EMaterialVertexFactory>;
}
