public native struct STonemappingACESParamsHDR {
  native let minStops: Float;
  native let maxStops: Float;
  native let midGrayScale: Float;
  native let surroundGamma: Float;
  native let toneCurveSaturation: Float;
  native let adjustWhitePoint: Bool;
  native let desaturate: Bool;
  native let dimSurround: Bool;
  native let tonemapLuminance: Bool;
  native let applyAfterLUT: Bool;
}
