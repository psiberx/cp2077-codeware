public abstract native class IMaterialDefinition extends IMaterial {
  public native let paramBlockSize: [Uint32; 3];
  public native let canHaveTangentUpdate: Bool;
  public native let canHaveDismemberment: Bool;
  public native let hasDPL: Bool;
  public native let canBeMasked: Bool;
  public native let shadingRateMode: EMaterialShadingRateMode;
  public native let materialVersion: Uint8;
  public native let vertexFactories: array<EMaterialVertexFactory>;
}
