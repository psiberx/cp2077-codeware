public native struct PSODescBlendModeDesc {
  native let numTargets: Uint8;
  native let independent: Bool;
  native let alphaToCoverage: Bool;
  native let renderTarget: [PSODescRenderTarget; 8];
}
