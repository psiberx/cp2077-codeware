public native struct PSODescBlendModeDesc {
  public native let numTargets: Uint8;
  public native let independent: Bool;
  public native let alphaToCoverage: Bool;
  public native let renderTarget: [PSODescRenderTarget; 8];
}
