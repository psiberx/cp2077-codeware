public native class questvehicleToNodeParams extends questVehicleSpecificCommandParams {
  public native let stopAtEnd: Bool;
  public native let nodeRef: NodeRef;
  public native let isPlayer: Bool;
  public native let useTraffic: Bool;
  public native let speedInTraffic: Float;
  public native let forceGreenLights: Bool;
  public native let portals: ref<vehiclePortalsList>;
  public native let trafficTryNeighborsForStart: Bool;
  public native let trafficTryNeighborsForEnd: Bool;
  public native let ignoreNoAIDrivingLanes: Bool;
}
