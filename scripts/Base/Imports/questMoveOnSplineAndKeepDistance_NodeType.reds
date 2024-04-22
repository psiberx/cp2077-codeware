public native class questMoveOnSplineAndKeepDistance_NodeType extends questIVehicleManagerNodeType {
  native let vehicleRef: EntityReference;
  native let keepDistanceFromRef: EntityReference;
  native let splineRef: NodeRef;
  native let distance: Float;
  native let blendTime: Float;
  native let minSpeed: Float;
  native let reduceSpeedOnTurns: Bool;
}
