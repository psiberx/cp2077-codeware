public native class vehiclePersistentDataPS extends GameComponentPS {
  native persistent let flags: Uint32;
  native persistent let autopilotPos: Float;
  native persistent let autopilotCurrentSpeed: Float;
  native persistent let isHackable: Bool;
  native persistent let questEnforcedTransform: Transform;
  native persistent let destruction: vehicleDestructionPSData;
  native persistent let audio: vehicleAudioPSData;
}
