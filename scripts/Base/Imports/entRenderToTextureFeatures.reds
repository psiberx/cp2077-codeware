public native struct entRenderToTextureFeatures {
  public native let renderDecals: Bool;
  public native let renderParticles: Bool;
  public native let renderForwardNoTXAA: Bool;
  public native let antiAliasing: entRenderToTextureFeaturesPlatform;
  public native let contactShadows: Bool;
  public native let localShadows: Bool;
  public native let SSAO: entRenderToTextureFeaturesPlatform;
  public native let reflections: entRenderToTextureFeaturesPlatform;
}
