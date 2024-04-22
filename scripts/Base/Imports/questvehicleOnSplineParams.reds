public native class questvehicleOnSplineParams extends questVehicleSpecificCommandParams {
  native let splineRef: NodeRef;
  native let reverseSpline: Bool;
  native let backwards: Bool;
  native let closest: Bool;
  native let forcedStartSpeed: Float;
  native let stopAtEnd: Bool;
  native let keepDistance: Bool;
  native let rubberBanding: Bool;
  native let audioCurvesParam: ref<vehicleAudioCurvesParam>;
}
