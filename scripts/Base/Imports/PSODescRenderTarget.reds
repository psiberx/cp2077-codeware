public native struct PSODescRenderTarget {
  public native let blendEnable: Bool;
  public native let writeMask: PSODescBlendModeWriteMask;
  public native let colorOp: PSODescBlendModeOp;
  public native let alphaOp: PSODescBlendModeOp;
  public native let destFactor: PSODescBlendModeFactor;
  public native let destAlphaFactor: PSODescBlendModeFactor;
  public native let srcFactor: PSODescBlendModeFactor;
  public native let srcAlphaFactor: PSODescBlendModeFactor;
}
