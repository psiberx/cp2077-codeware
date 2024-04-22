public native struct SOMState {
  native let depthStencilModeDesc: PSODescDepthStencilModeDesc;
  native let rasterizerModeDesc: PSODescRasterizerModeDesc;
  native let blendModeDesc: PSODescBlendModeDesc;
  native let stencilReadMask: Uint8;
  native let stencilWriteMask: Uint8;
  native let stencilRef: Uint8;
}
