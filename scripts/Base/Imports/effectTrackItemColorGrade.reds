public native class effectTrackItemColorGrade extends effectTrackItem {
  public native let contrast: effectEffectParameterEvaluatorFloat;
  public native let saturate: effectEffectParameterEvaluatorFloat;
  public native let brightness: effectEffectParameterEvaluatorFloat;
  public native let lutWeight: effectEffectParameterEvaluatorFloat;
  public native let lutParams: ColorGradingLutParams;
  public native let lutParamsHdr: ColorGradingLutParams;
  public native let blendWithBaseLut: Bool;
  public native let mask: array<ERenderObjectType>;
}
