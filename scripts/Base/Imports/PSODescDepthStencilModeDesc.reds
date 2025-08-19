public native struct PSODescDepthStencilModeDesc {
  public native let depthTestEnable: Bool;
  public native let depthWriteEnable: Bool;
  public native let depthFunc: PSODescDepthStencilModeComparisonMode;
  public native let stencilEnable: Bool;
  public native let stencilReadMask: Bool;
  public native let stencilWriteMask: Bool;
  public native let frontFace: PSODescStencilFuncDesc;
}
