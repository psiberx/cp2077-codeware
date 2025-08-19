@mixedRef()
public native class audioRadioStationMetadata extends audioAudioMetadata {
  public native let tracks: array<CName>;
  public native let blips: array<audioRadioBlip>;
  public native let speaker: audioRadioSpeakerType;
}
