public native class questvehicleChaseParams extends questVehicleSpecificCommandParams {
  public native let targetEntRef: EntityReference;
  public native let isPlayer: Bool;
  public native let distanceMin: Float;
  public native let distanceMax: Float;
  public native let forceStartSpeed: Float;
  public native let aggressiveRammingEnabled: Bool;
  public native let ignoreChaseVehiclesLimit: Bool;
  public native let boostDrivingStats: Bool;
}
