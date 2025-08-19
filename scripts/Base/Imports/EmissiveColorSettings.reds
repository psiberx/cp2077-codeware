public native class EmissiveColorSettings extends IAreaSettings {
  public native let tint: CurveDataHDRColor;
  public native let saturation: CurveDataFloat;
  public native let brigtness: CurveDataFloat;
  public native let exposure: CurveDataVector2;
  public native let cameraLuminance: CurveDataVector2;
  public native let evBlend: CurveDataFloat;
  public native let exposureIBL: CurveDataFloat;
  public native let luminanceIBL: CurveDataFloat;
  public native let curveRampIBL: Float;
  public native let exposureScale: CurveDataFloat;
}
