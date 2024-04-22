public native class questvehicleChaseParams extends questVehicleSpecificCommandParams {
  native let targetEntRef: EntityReference;
  native let isPlayer: Bool;
  native let distanceMin: Float;
  native let distanceMax: Float;
  native let forceStartSpeed: Float;
  native let aggressiveRammingEnabled: Bool;
  native let ignoreChaseVehiclesLimit: Bool;
  native let boostDrivingStats: Bool;
}
