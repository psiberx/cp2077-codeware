public native class questvehicleToNodeParams extends questVehicleSpecificCommandParams {
  native let stopAtEnd: Bool;
  native let nodeRef: NodeRef;
  native let isPlayer: Bool;
  native let useTraffic: Bool;
  native let speedInTraffic: Float;
  native let forceGreenLights: Bool;
  native let portals: ref<vehiclePortalsList>;
  native let trafficTryNeighborsForStart: Bool;
  native let trafficTryNeighborsForEnd: Bool;
  native let ignoreNoAIDrivingLanes: Bool;
}
