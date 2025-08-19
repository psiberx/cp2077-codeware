public native struct vehicleAudioPSData {
  public native persistent let activeRadioStation: CName;
  public native persistent let acousticIsolationFactor: Float;
  public native persistent let glassAcousticIsolationFactor: Float;
  public native persistent let isPlayerVehicleSummoned: Bool;
  public native persistent let openedWindows: [CName; 6];
}
