public native class questvehicleFollowParams extends questVehicleSpecificCommandParams {
  public native let targetEntRef: EntityReference;
  public native let distanceMin: Float;
  public native let distanceMax: Float;
  public native let isPlayer: Bool;
  public native let stopWhenTargetReached: Bool;
  public native let useTraffic: Bool;
  public native let trafficTryNeighborsForStart: Bool;
  public native let trafficTryNeighborsForEnd: Bool;
}
