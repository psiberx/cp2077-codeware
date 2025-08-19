@mixedRef()
public native class audioAcousticZoneMetadata extends audioAudioMetadata {
  public native let priority: Int32;
  public native let bleadingDistance: Float;
  public native let eventsOnEnter: array<CName>;
  public native let eventsOnExit: array<CName>;
  public native let eventsOnActive: array<CName>;
  public native let soundBanks: array<CName>;
  public native let parameters: array<audioAcousticZoneParameterMapItem>;
  public native let reverbSettings: CName;
  public native let voReverbSettings: CName;
  public native let footstepMaterialOverride: CName;
}
