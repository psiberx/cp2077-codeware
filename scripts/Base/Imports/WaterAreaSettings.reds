public native class WaterAreaSettings extends IAreaSettings {
  public native let blurMin: Float;
  public native let blurMax: Float;
  public native let blurExponent: Float;
  public native let depth: Float;
  public native let density: Float;
  public native let lightAbsorptionColor: HDRColor;
  public native let lightDecayColor: HDRColor;
  public native let globalWaterMask: ResourceRef; // rRef<CBitmapTexture>
  public native let windDir: CurveDataFloat;
  public native let windSpeed: CurveDataFloat;
  public native let windScale: CurveDataFloat;
  public native let amplitude: CurveDataFloat;
  public native let lambda: CurveDataFloat;
}
