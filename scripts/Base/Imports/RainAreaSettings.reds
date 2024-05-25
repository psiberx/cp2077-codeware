public native class RainAreaSettings extends IAreaSettings {
  native let numParticles: Uint32;
  native let radius: Float;
  native let heightRange: Float;
  native let globalLightResponse: Float;
  native let tiling: CurveDataFloat;
  native let porosityThresholdStart: Float;
  native let porosityThresholdEnd: Float;
  native let glossinessFactor: Float;
  native let baseColorFactor: Float;
  native let moistureAccumulationSpeed: Float;
  native let puddlesAccumulationSpeed: Float;
  native let moistureEvaporationSpeed: Float;
  native let puddlesEvaporationSpeed: Float;
  native let rainIntensity: CurveDataFloat;
  native let rainOverride: CurveDataFloat;
  native let rainMoistureOverride: CurveDataFloat;
  native let rainPuddlesOverride: CurveDataFloat;
  native let waterRainIntensity: Float;
  native let rainleaksMask: ResourceRef; // rRef<CBitmapTexture>
  native let raindropsMask: ResourceRef; // rRef<CBitmapTexture>
  native let rainRipplesMask: ResourceRef; // rRef<CBitmapTexture>
}
