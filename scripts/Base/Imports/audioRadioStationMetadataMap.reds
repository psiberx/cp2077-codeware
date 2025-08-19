@mixedRef()
public native class audioRadioStationMetadataMap extends audioAudioMetadata {
  public native let radioStations: array<CName>;
  public native let switchStationEvent: CName;
  public native let turnOnRadioEvent: CName;
  public native let turnOffRadioEvent: CName;
  public native let defaultBackgroundJingle: audioRadioStationJingleMetadata;
}
