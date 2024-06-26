public native class CloudAreaSettings extends IAreaSettings {
  native let cloudSunShadowFaloff: CurveDataFloat;
  native let cloudSunScattering: CurveDataFloat;
  native let cloudMoonScattering: CurveDataFloat;
  native let cloudLightColor: CurveDataHDRColor;
  native let cloudAmbientIntensity: CurveDataFloat;
  native let cloudCirrusOpacity: CurveDataFloat;
  native let cloudCirrusScale: CurveDataFloat;
  native let cloudCirrusAltitude: CurveDataFloat;
  native let cloudCirrusTexture: ResourceRef; // rRef<CBitmapTexture>
  native let volWeatherTexture: ResourceRef; // rRef<CBitmapTexture>
  native let volNoiseTexture: ResourceRef; // rRef<CBitmapTexture>
  native let volHorizonCoverage: Float;
  native let volCoverage: CurveDataFloat;
  native let volDensity: CurveDataFloat;
  native let cloudsBottom: Float;
  native let cloudsTop: Float;
  native let rayStartOffset: Float;
  native let rayStartFalloff: Float;
  native let lightIntensity: CurveDataFloat;
  native let reflectionProbeLightIntensity: CurveDataFloat;
  native let shadowIntensity: CurveDataFloat;
  native let worldShadowIntensity: CurveDataFloat;
  native let ambientIntensity: CurveDataFloat;
  native let ambientOutscatter: CurveDataFloat;
  native let inScatter: Float;
  native let outScatter: Float;
  native let inVsOutScatter: Float;
  native let silverLining: Float;
  native let volCoverageWindInfluence: Float;
  native let volNoiseWindInfluence: Float;
  native let volDetailWindInfluence: Float;
  native let volDistantFogOpacity: Float;
  native let volCoverageOffset: Vector2;
}
