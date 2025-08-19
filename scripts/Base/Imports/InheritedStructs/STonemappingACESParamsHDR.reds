public native struct STonemappingACESParamsHDR {
  public native let minStops: Float;
  public native let maxStops: Float;
  public native let midGrayScale: Float;
  public native let surroundGamma: Float;
  public native let toneCurveSaturation: Float;
  public native let adjustWhitePoint: Bool;
  public native let desaturate: Bool;
  public native let dimSurround: Bool;
  public native let tonemapLuminance: Bool;
  public native let applyAfterLUT: Bool;
}
