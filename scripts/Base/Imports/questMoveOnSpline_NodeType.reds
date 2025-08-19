public native class questMoveOnSpline_NodeType extends questIVehicleManagerNodeType {
  public native let vehicleRef: EntityReference;
  public native let splineRef: NodeRef;
  public native let startFrom: Float;
  public native let blendType: vehiclePlayerToAIInterpolationType;
  public native let blendTime: Float;
  public native let reverseGear: Bool;
  public native let arriveWithPivot: Bool;
  public native let trafficDeletionMode: vehicleAIPathTrafficDeletionMode;
  public native let sceneBlendInDistance: Float;
  public native let sceneBlendOutDistance: Float;
  public native let overrides: ref<questIVehicleMoveOnSpline_Overrides>;
  public native let audioCurves: ResourceRef; // rRef<vehicleAudioVehicleCurveSet>
}
