public native struct vehicleAudioPSData {
  native persistent let activeRadioStation: CName;
  native persistent let acousticIsolationFactor: Float;
  native persistent let glassAcousticIsolationFactor: Float;
  native persistent let isPlayerVehicleSummoned: Bool;
  native persistent let openedWindows: [CName; 6];
}
