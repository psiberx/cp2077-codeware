public native class questVehicleCommandParams extends AICommandParams {
  native let type: questVehicleCommandType;
  native let additionalParamsOnSpline: ref<questvehicleOnSplineParams>;
  native let additionalParamsFollow: ref<questvehicleFollowParams>;
  native let additionalParamsToNode: ref<questvehicleToNodeParams>;
  native let additionalParamsRacing: ref<questvehicleRacingParams>;
  native let additionalParamsJoinTraffic: ref<questvehicleJoinTrafficParams>;
  native let additionalParamsPanic: ref<questvehiclePanicParams>;
  native let additionalParamsChase: ref<questvehicleChaseParams>;
}
