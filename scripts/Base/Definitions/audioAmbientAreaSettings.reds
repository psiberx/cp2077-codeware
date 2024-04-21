public native class audioAmbientAreaSettings extends audioAudioMetadata {
  native let MetadataParent: CName;
  native let EmitterDecorator: CName;
  native let Priority: Int32;
  native let EventsOnEnter: array<audioAudEventStruct>;
  native let EventsOnExit: array<audioAudEventStruct>;
  native let EventsOnActive: array<audioAudEventStruct>;
  native let SoundBanks: array<audioSoundBankStruct>;
  native let Switches: array<audioAudSwitch>;
  native let Parameters: array<audioAudParameter>;
  native let Reverb: CName;
  native let reverbTransitionTime: Float;
  native let VoReverb: CName;
  native let FootstepMaterialOverride: CName;
  native let soundsLimitingSettings: CName;
  native let isMusic: Bool;
  native let groupingSettings: audioAmbientAreaGroupingSettings;
  native let quadSettings: audioQuadEmitterSettings;
  native let outerDistance: Float;
  native let verticalOuterDistance: Float;
  native let insideSourceDistance: Float;
  native let eventOverrides: CName;
  native let outdoornessOverride: Bool;
  native let outdoorness: Float;
  native let mergeRoomsWithinArea: Bool;
  native let mixingContext: CName;
  native let ambientPaletteEntries: array<audioAmbientPaletteEntry>;
}
