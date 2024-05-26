public native class EmissiveColorSettings extends IAreaSettings {
  native let tint: CurveDataHDRColor;
  native let saturation: CurveDataFloat;
  native let brigtness: CurveDataFloat;
  native let exposure: CurveDataVector2;
  native let cameraLuminance: CurveDataVector2;
  native let evBlend: CurveDataFloat;
  native let exposureIBL: CurveDataFloat;
  native let luminanceIBL: CurveDataFloat;
  native let curveRampIBL: Float;
  native let exposureScale: CurveDataFloat;
}
