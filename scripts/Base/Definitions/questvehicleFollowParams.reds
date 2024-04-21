public native class questvehicleFollowParams extends questVehicleSpecificCommandParams {
  native let targetEntRef: EntityReference;
  native let distanceMin: Float;
  native let distanceMax: Float;
  native let isPlayer: Bool;
  native let stopWhenTargetReached: Bool;
  native let useTraffic: Bool;
  native let trafficTryNeighborsForStart: Bool;
  native let trafficTryNeighborsForEnd: Bool;
}
