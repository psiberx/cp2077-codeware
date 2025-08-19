@mixedRef()
public native class audioAmbientAreaSettings extends audioAudioMetadata {
  public native let MetadataParent: CName;
  public native let EmitterDecorator: CName;
  public native let Priority: Int32;
  public native let EventsOnEnter: array<audioAudEventStruct>;
  public native let EventsOnExit: array<audioAudEventStruct>;
  public native let EventsOnActive: array<audioAudEventStruct>;
  public native let SoundBanks: array<audioSoundBankStruct>;
  public native let Switches: array<audioAudSwitch>;
  public native let Parameters: array<audioAudParameter>;
  public native let Reverb: CName;
  public native let reverbTransitionTime: Float;
  public native let VoReverb: CName;
  public native let FootstepMaterialOverride: CName;
  public native let soundsLimitingSettings: CName;
  public native let isMusic: Bool;
  public native let groupingSettings: audioAmbientAreaGroupingSettings;
  public native let quadSettings: audioQuadEmitterSettings;
  public native let outerDistance: Float;
  public native let verticalOuterDistance: Float;
  public native let insideSourceDistance: Float;
  public native let eventOverrides: CName;
  public native let outdoornessOverride: Bool;
  public native let outdoorness: Float;
  public native let mergeRoomsWithinArea: Bool;
  public native let mixingContext: CName;
  public native let ambientPaletteEntries: array<audioAmbientPaletteEntry>;
}
