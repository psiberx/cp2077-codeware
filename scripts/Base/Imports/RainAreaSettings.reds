public native class RainAreaSettings extends IAreaSettings {
  public native let numParticles: Uint32;
  public native let radius: Float;
  public native let heightRange: Float;
  public native let globalLightResponse: Float;
  public native let tiling: CurveDataFloat;
  public native let porosityThresholdStart: Float;
  public native let porosityThresholdEnd: Float;
  public native let glossinessFactor: Float;
  public native let baseColorFactor: Float;
  public native let moistureAccumulationSpeed: Float;
  public native let puddlesAccumulationSpeed: Float;
  public native let moistureEvaporationSpeed: Float;
  public native let puddlesEvaporationSpeed: Float;
  public native let rainIntensity: CurveDataFloat;
  public native let rainOverride: CurveDataFloat;
  public native let rainMoistureOverride: CurveDataFloat;
  public native let rainPuddlesOverride: CurveDataFloat;
  public native let waterRainIntensity: Float;
  public native let rainleaksMask: ResourceRef; // rRef<CBitmapTexture>
  public native let raindropsMask: ResourceRef; // rRef<CBitmapTexture>
  public native let rainRipplesMask: ResourceRef; // rRef<CBitmapTexture>
}
