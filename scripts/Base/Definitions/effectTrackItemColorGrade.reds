public native class effectTrackItemColorGrade extends effectTrackItem {
  native let contrast: effectEffectParameterEvaluatorFloat;
  native let saturate: effectEffectParameterEvaluatorFloat;
  native let brightness: effectEffectParameterEvaluatorFloat;
  native let lutWeight: effectEffectParameterEvaluatorFloat;
  native let lutParams: ColorGradingLutParams;
  native let lutParamsHdr: ColorGradingLutParams;
  native let blendWithBaseLut: Bool;
  native let mask: array<ERenderObjectType>;
}
