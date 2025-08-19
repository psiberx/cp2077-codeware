@mixedRef()
public native class audioVehicleMetadata extends audioCustomEmitterMetadata {
  public native let generalData: audioVehicleGeneralData;
  public native let mechanicalData: audioVehicleMechanicalData;
  public native let wheelData: audioVehicleWheelData;
  public native let emitterPositionData: audioVehicleEmitterPositionData;
  public native let minRpm: Float;
  public native let maxRpm: Float;
  public native let vehicleCollisionSettings: CName;
  public native let vehicleGridDestructionSettings: CName;
  public native let vehiclePartSettings: CName;
  public native let collisionCooldown: Float;
  public native let maxPlayingDistance: Float;
  public native let dopplerFactor: Float;
  public native let suspensionSqueekTimeout: Float;
  public native let exitDelay: Float;
  public native let gearSweeteners: array<CName>;
  public native let testWheelMaterial: Bool;
  public native let hasRadioReceiver: Bool;
  public native let usesPoliceRadioStation: Bool;
  public native let acousticIsolationFactor: Float;
  public native let trafficEmitterMetadata: CName;
  public native let radioReceiverType: CName;
  public native let matchingStartupRadioStations: array<CName>;
  public native let radioPlaysWhenEngineStartsProbability: Float;
}
