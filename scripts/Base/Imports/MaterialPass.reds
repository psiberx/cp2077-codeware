public native struct MaterialPass {
  public native let stagePassNameRegular: CName;
  public native let stagePassNameDiscarded: CName;
  public native let depthStencilMode: PSODescDepthStencilModeDesc;
  public native let rasterizerMode: PSODescRasterizerModeDesc;
  public native let blendMode: PSODescBlendModeDesc;
  public native let stencilReadMask: Uint8;
  public native let stencilWriteMask: Uint8;
  public native let stencilRef: Uint8;
  public native let orderIndex: Uint8;
  public native let enablePixelShader: Bool;
}
