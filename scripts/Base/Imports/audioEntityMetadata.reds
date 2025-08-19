@mixedRef()
public native class audioEntityMetadata extends audioAudioMetadata {
  public native let fallbackDecorators: array<CName>;
  public native let defaultPositionName: CName;
  public native let defaultEmitterName: CName;
  public native let isDefaultForEntityType: CName;
  public native let preferSoundComponentPosition: Bool;
  public native let priority: Int32;
  public native let rigMetadata: CName;
  public native let emitterDescriptions: array<audioEntityEmitterSettings>;
  public native let alwaysCreateDefaultEmitter: Bool;
}
