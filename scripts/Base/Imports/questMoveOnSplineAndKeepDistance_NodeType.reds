public native class questMoveOnSplineAndKeepDistance_NodeType extends questIVehicleManagerNodeType {
  public native let vehicleRef: EntityReference;
  public native let keepDistanceFromRef: EntityReference;
  public native let splineRef: NodeRef;
  public native let distance: Float;
  public native let blendTime: Float;
  public native let minSpeed: Float;
  public native let reduceSpeedOnTurns: Bool;
}
