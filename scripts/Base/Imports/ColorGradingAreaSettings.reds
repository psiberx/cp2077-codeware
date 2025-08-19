public native class ColorGradingAreaSettings extends IAreaSettings {
  public native let contrast: Float;
  public native let contrastPivot: Float;
  public native let saturation: Float;
  public native let hue: Float;
  public native let brightness: Float;
  public native let lift: ColorBalance;
  public native let gammaValue: ColorBalance;
  public native let gain: ColorBalance;
  public native let offset: ColorBalance;
  public native let lowRange: Float;
  public native let shadowOffset: ColorBalance;
  public native let midtoneOffset: ColorBalance;
  public native let highRange: Float;
  public native let highlightOffset: ColorBalance;
  public native let ldrLut: ColorGradingLutParams;
  public native let hdrLut: ColorGradingLutParams;
  public native let forceHdrLut: Bool;
}
