public native struct PSODescDepthStencilModeDesc {
  native let depthTestEnable: Bool;
  native let depthWriteEnable: Bool;
  native let depthFunc: PSODescDepthStencilModeComparisonMode;
  native let stencilEnable: Bool;
  native let stencilReadMask: Bool;
  native let stencilWriteMask: Bool;
  native let frontFace: PSODescStencilFuncDesc;
}
