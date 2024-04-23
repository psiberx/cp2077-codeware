public native class questMoveOnSpline_NodeType extends questIVehicleManagerNodeType {
  native let vehicleRef: EntityReference;
  native let splineRef: NodeRef;
  native let startFrom: Float;
  native let blendType: vehiclePlayerToAIInterpolationType;
  native let blendTime: Float;
  native let reverseGear: Bool;
  native let arriveWithPivot: Bool;
  native let trafficDeletionMode: vehicleAIPathTrafficDeletionMode;
  native let sceneBlendInDistance: Float;
  native let sceneBlendOutDistance: Float;
  native let overrides: ref<questIVehicleMoveOnSpline_Overrides>;
  native let audioCurves: ResourceRef; // rRef<vehicleAudioVehicleCurveSet>
}
