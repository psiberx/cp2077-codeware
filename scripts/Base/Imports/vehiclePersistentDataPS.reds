public native class vehiclePersistentDataPS extends GameComponentPS {
  public native persistent let flags: Uint32;
  public native persistent let autopilotPos: Float;
  public native persistent let autopilotCurrentSpeed: Float;
  public native persistent let isHackable: Bool;
  public native persistent let wheelRuntimeData: [vehicleWheelRuntimePSData; 4];
  public native persistent let questEnforcedTransform: Transform;
  public native persistent let destruction: vehicleDestructionPSData;
  public native persistent let audio: vehicleAudioPSData;
}
