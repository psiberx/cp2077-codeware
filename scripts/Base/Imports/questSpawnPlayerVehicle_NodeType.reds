public native class questSpawnPlayerVehicle_NodeType extends questIVehicleManagerNodeType {
  public native let despawn: Bool;
  public native let positionRef: ref<questUniversalRef>;
  public native let offset: Vector3;
  public native let driveIn: Bool;
  public native let vehicle: String;
  public native let vehicleGlobalName: CName;
  public native let despawnAllEnabledVehicles: Bool;
  public native let retryUntilStubCreated: Bool;
}
