public native class audioEntityMetadata extends audioAudioMetadata {
  native let fallbackDecorators: array<CName>;
  native let defaultPositionName: CName;
  native let defaultEmitterName: CName;
  native let isDefaultForEntityType: CName;
  native let preferSoundComponentPosition: Bool;
  native let priority: Int32;
  native let rigMetadata: CName;
  native let emitterDescriptions: array<audioEntityEmitterSettings>;
  native let alwaysCreateDefaultEmitter: Bool;
}
