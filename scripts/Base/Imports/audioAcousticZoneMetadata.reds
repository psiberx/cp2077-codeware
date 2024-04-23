public native class audioAcousticZoneMetadata extends audioAudioMetadata {
  native let priority: Int32;
  native let bleadingDistance: Float;
  native let eventsOnEnter: array<CName>;
  native let eventsOnExit: array<CName>;
  native let eventsOnActive: array<CName>;
  native let soundBanks: array<CName>;
  native let parameters: array<audioAcousticZoneParameterMapItem>;
  native let reverbSettings: CName;
  native let voReverbSettings: CName;
  native let footstepMaterialOverride: CName;
}
