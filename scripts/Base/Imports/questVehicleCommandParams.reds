public native class questVehicleCommandParams extends AICommandParams {
  public native let type: questVehicleCommandType;
  public native let additionalParamsOnSpline: ref<questvehicleOnSplineParams>;
  public native let additionalParamsFollow: ref<questvehicleFollowParams>;
  public native let additionalParamsToNode: ref<questvehicleToNodeParams>;
  public native let additionalParamsRacing: ref<questvehicleRacingParams>;
  public native let additionalParamsJoinTraffic: ref<questvehicleJoinTrafficParams>;
  public native let additionalParamsPanic: ref<questvehiclePanicParams>;
  public native let additionalParamsChase: ref<questvehicleChaseParams>;
}
