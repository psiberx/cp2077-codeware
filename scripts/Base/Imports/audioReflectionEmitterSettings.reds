@mixedRef()
public native class audioReflectionEmitterSettings extends audioAudioMetadata {
  public native let reflectionEvent: CName;
  public native let fadeout: Float;
  public native let reflectionDeltaThreshold: Float;
  public native let maxConcurrentReflections: Uint32;
  public native let broadcastChannel: Uint32;
  public native let listenerRelativePosition: Bool;
  public native let upReflectionEnabled: Bool;
  public native let shortReflectionIndoors: Bool;
  public native let reflectionVariant: audioReflectionVariant;
  public native let backReflectionCutoffSpread: Float;
  public native let backReflectionCutoffStrength: Float;
  public native let backReflectionCutoffSoftness: Float;
  public native let farReflectionDistance: Float;
  public native let nearReflectionDistance: Float;
  public native let minimumFaceAlignement: Float;
  public native let fixedRaycastPitch: Float;
}
