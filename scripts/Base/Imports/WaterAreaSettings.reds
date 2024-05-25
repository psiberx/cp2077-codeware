public native class WaterAreaSettings extends IAreaSettings {
  native let blurMin: Float;
  native let blurMax: Float;
  native let blurExponent: Float;
  native let depth: Float;
  native let density: Float;
  native let lightAbsorptionColor: HDRColor;
  native let lightDecayColor: HDRColor;
  native let globalWaterMask: ResourceRef; // rRef<CBitmapTexture>
  native let windDir: CurveDataFloat;
  native let windSpeed: CurveDataFloat;
  native let windScale: CurveDataFloat;
  native let amplitude: CurveDataFloat;
  native let lambda: CurveDataFloat;
}
