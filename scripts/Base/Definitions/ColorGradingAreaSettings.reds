public native class ColorGradingAreaSettings extends IAreaSettings {
  native let contrast: Float;
  native let contrastPivot: Float;
  native let saturation: Float;
  native let hue: Float;
  native let brightness: Float;
  native let lift: ColorBalance;
  native let gammaValue: ColorBalance;
  native let gain: ColorBalance;
  native let offset: ColorBalance;
  native let lowRange: Float;
  native let shadowOffset: ColorBalance;
  native let midtoneOffset: ColorBalance;
  native let highRange: Float;
  native let highlightOffset: ColorBalance;
  native let ldrLut: ColorGradingLutParams;
  native let hdrLut: ColorGradingLutParams;
  native let forceHdrLut: Bool;
}
