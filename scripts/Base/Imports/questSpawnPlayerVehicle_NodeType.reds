public native class questSpawnPlayerVehicle_NodeType extends questIVehicleManagerNodeType {
  native let despawn: Bool;
  native let positionRef: ref<questUniversalRef>;
  native let offset: Vector3;
  native let driveIn: Bool;
  native let vehicle: String;
  native let vehicleGlobalName: CName;
  native let despawnAllEnabledVehicles: Bool;
  native let retryUntilStubCreated: Bool;
}
