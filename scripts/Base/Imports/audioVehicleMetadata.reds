public native class audioVehicleMetadata extends audioCustomEmitterMetadata {
  native let generalData: audioVehicleGeneralData;
  native let mechanicalData: audioVehicleMechanicalData;
  native let wheelData: audioVehicleWheelData;
  native let emitterPositionData: audioVehicleEmitterPositionData;
  native let minRpm: Float;
  native let maxRpm: Float;
  native let vehicleCollisionSettings: CName;
  native let vehicleGridDestructionSettings: CName;
  native let vehiclePartSettings: CName;
  native let collisionCooldown: Float;
  native let maxPlayingDistance: Float;
  native let dopplerFactor: Float;
  native let suspensionSqueekTimeout: Float;
  native let exitDelay: Float;
  native let gearSweeteners: array<CName>;
  native let testWheelMaterial: Bool;
  native let hasRadioReceiver: Bool;
  native let usesPoliceRadioStation: Bool;
  native let acousticIsolationFactor: Float;
  native let trafficEmitterMetadata: CName;
  native let radioReceiverType: CName;
  native let matchingStartupRadioStations: array<CName>;
  native let radioPlaysWhenEngineStartsProbability: Float;
}
