public native class questvehicleOnSplineParams extends questVehicleSpecificCommandParams {
  public native let splineRef: NodeRef;
  public native let reverseSpline: Bool;
  public native let backwards: Bool;
  public native let closest: Bool;
  public native let forcedStartSpeed: Float;
  public native let stopAtEnd: Bool;
  public native let keepDistance: Bool;
  public native let keepDistanceParam: ref<questParamKeepDistance>;
  public native let rubberBanding: Bool;
  public native let rubberBandingParam: ref<questParamRubberbanding>;
  public native let audioCurvesParam: ref<vehicleAudioCurvesParam>;
}
