public native struct PSODescRenderTarget {
  native let blendEnable: Bool;
  native let writeMask: PSODescBlendModeWriteMask;
  native let colorOp: PSODescBlendModeOp;
  native let alphaOp: PSODescBlendModeOp;
  native let destFactor: PSODescBlendModeFactor;
  native let destAlphaFactor: PSODescBlendModeFactor;
  native let srcFactor: PSODescBlendModeFactor;
  native let srcAlphaFactor: PSODescBlendModeFactor;
}
