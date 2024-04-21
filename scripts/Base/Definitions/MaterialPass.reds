public native struct MaterialPass {
  native let stagePassNameRegular: CName;
  native let stagePassNameDiscarded: CName;
  native let depthStencilMode: PSODescDepthStencilModeDesc;
  native let rasterizerMode: PSODescRasterizerModeDesc;
  native let blendMode: PSODescBlendModeDesc;
  native let stencilReadMask: Uint8;
  native let stencilWriteMask: Uint8;
  native let stencilRef: Uint8;
  native let orderIndex: Uint8;
  native let enablePixelShader: Bool;
}
