public native class EnvProbeComponent extends IVisualComponent {
  public native let isEnabled: Bool;
  public native let size: Vector3;
  public native let edgeScale: Vector3;
  public native let emissiveScale: Float;
  public native let globalProbe: Bool;
  public native let boxProjection: Bool;
  public native let allInShadow: Bool;
  public native let streamingDistance: Float;
  public native let streamingHeight: Float;
  public native let blendRange: Uint8;
  public native let neighborMode: envUtilsNeighborMode;
  public native let hideSkyColor: Bool;
  public native let ambientMode: envUtilsReflectionProbeAmbientContributionMode;
  public native let brightnessEVClamp: Uint8;
  public native let probeDataRef: ResourceAsyncRef; // raRef<CReflectionProbeDataResource>
  public native let priority: Uint8;
}
