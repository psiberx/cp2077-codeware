public native class worldReflectionProbeNode extends worldNode {
  public native let probeDataRef: ResourceAsyncRef; // raRef<CReflectionProbeDataResource>
  public native let priority: Uint8;
  public native let globalProbe: Bool;
  public native let boxProjection: Bool;
  public native let neighborMode: envUtilsNeighborMode;
  public native let edgeScale: Vector3;
  public native let emissiveScale: Float;
  public native let reflectionDimming: Float;
  public native let simpleFogColor: HDRColor;
  public native let simpleFogDensity: Float;
  public native let skyScale: Float;
  public native let allInShadow: Bool;
  public native let hideSkyColor: Bool;
  public native let volFogAmbient: Bool;
  public native let brightnessEVClamp: Int8;
  public native let ambientMode: envUtilsReflectionProbeAmbientContributionMode;
  public native let captureOffset: Vector3;
  public native let nearClipDistance: Float;
  public native let farClipDistance: Float;
  public native let blendRange: Uint8;
  public native let streamingDistance: Float;
  public native let streamingHeight: Float;
  public native let subScene: Bool;
  public native let noFadeBlend: Bool;
}
