public native class CloudAreaSettings extends IAreaSettings {
  public native let cloudSunShadowFaloff: CurveDataFloat;
  public native let cloudSunScattering: CurveDataFloat;
  public native let cloudMoonScattering: CurveDataFloat;
  public native let cloudLightColor: CurveDataHDRColor;
  public native let cloudAmbientIntensity: CurveDataFloat;
  public native let cloudCirrusOpacity: CurveDataFloat;
  public native let cloudCirrusScale: CurveDataFloat;
  public native let cloudCirrusAltitude: CurveDataFloat;
  public native let cloudCirrusTexture: ResourceRef; // rRef<CBitmapTexture>
  public native let volWeatherTexture: ResourceRef; // rRef<CBitmapTexture>
  public native let volNoiseTexture: ResourceRef; // rRef<CBitmapTexture>
  public native let volHorizonCoverage: Float;
  public native let volCoverage: CurveDataFloat;
  public native let volDensity: CurveDataFloat;
  public native let cloudsBottom: Float;
  public native let cloudsTop: Float;
  public native let rayStartOffset: Float;
  public native let rayStartFalloff: Float;
  public native let lightIntensity: CurveDataFloat;
  public native let reflectionProbeLightIntensity: CurveDataFloat;
  public native let shadowIntensity: CurveDataFloat;
  public native let worldShadowIntensity: CurveDataFloat;
  public native let ambientIntensity: CurveDataFloat;
  public native let ambientOutscatter: CurveDataFloat;
  public native let inScatter: Float;
  public native let outScatter: Float;
  public native let inVsOutScatter: Float;
  public native let silverLining: Float;
  public native let volCoverageWindInfluence: Float;
  public native let volNoiseWindInfluence: Float;
  public native let volDetailWindInfluence: Float;
  public native let volDistantFogOpacity: Float;
  public native let volCoverageOffset: Vector2;
}
