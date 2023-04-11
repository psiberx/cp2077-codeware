public native class EnvProbeComponent extends IVisualComponent {
  native let isEnabled: Bool;
  native let size: Vector3;
  native let edgeScale: Vector3;
  native let emissiveScale: Float;
  native let globalProbe: Bool;
  native let boxProjection: Bool;
  native let allInShadow: Bool;
  native let streamingDistance: Float;
  native let streamingHeight: Float;
  native let blendRange: Uint8;
  native let neighborMode: envUtilsNeighborMode;
  native let hideSkyColor: Bool;
  native let ambientMode: envUtilsReflectionProbeAmbientContributionMode;
  native let brightnessEVClamp: Uint8;
  native let probeDataRef: ResourceAsyncRef;
  native let priority: Uint8;
}
