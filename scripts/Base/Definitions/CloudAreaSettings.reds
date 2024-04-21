public native class CloudAreaSettings extends IAreaSettings {
  native let cloudCirrusTexture: ResourceRef; // rRef<CBitmapTexture>
  native let volWeatherTexture: ResourceRef; // rRef<CBitmapTexture>
  native let volNoiseTexture: ResourceRef; // rRef<CBitmapTexture>
  native let volHorizonCoverage: Float;
  native let cloudsBottom: Float;
  native let cloudsTop: Float;
  native let rayStartOffset: Float;
  native let rayStartFalloff: Float;
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
