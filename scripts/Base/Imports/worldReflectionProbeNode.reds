public native class worldReflectionProbeNode extends worldNode {
  native let probeDataRef: ResourceAsyncRef; // raRef<CReflectionProbeDataResource>
  native let priority: Uint8;
  native let globalProbe: Bool;
  native let boxProjection: Bool;
  native let neighborMode: envUtilsNeighborMode;
  native let edgeScale: Vector3;
  native let emissiveScale: Float;
  native let reflectionDimming: Float;
  native let simpleFogColor: HDRColor;
  native let simpleFogDensity: Float;
  native let skyScale: Float;
  native let allInShadow: Bool;
  native let hideSkyColor: Bool;
  native let volFogAmbient: Bool;
  native let brightnessEVClamp: Int8;
  native let ambientMode: envUtilsReflectionProbeAmbientContributionMode;
  native let captureOffset: Vector3;
  native let nearClipDistance: Float;
  native let farClipDistance: Float;
  native let blendRange: Uint8;
  native let streamingDistance: Float;
  native let streamingHeight: Float;
  native let subScene: Bool;
  native let noFadeBlend: Bool;
}
