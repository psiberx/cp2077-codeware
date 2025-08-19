@mixedRef()
public native class audioDirectorSystemSettings extends audioAudioMetadata {
  public native let combatVoManagerSettingsName: CName;
  public native let singleConversationMinRepeatTime: Float;
  public native let allConversationsMinRepeatTime: Float;
  public native let maxVelocityMagnitudeToConsiderPlayerVehicleInactive: Float;
  public native let maxVelocityMagnitudeToConsiderTrafficVehicleIdle: Float;
  public native let playerInactiveMinTimeNeededToEngageMovingFaster: Float;
  public native let vehEngageMovingFasterInterpolation: audioVehicleEngageMovingFasterInterpolationData;
  public native let playerBrakeEventCooldown: Float;
  public native let trafficSpeedRC: Float;
  public native let trafficAccelerationRC: Float;
  public native let trafficRpmRC: Float;
  public native let trafficSlipRatioSkidThreshold: Float;
  public native let trafficHornSingleVehicleCooldown: Float;
  public native let trafficHornAllVehiclesCooldown: Float;
  public native let trafficHornMaxDistanceRangeToPlayer: Float;
  public native let overHeadVisibilityMaxOcclusion: Float;
  public native let overHeadVisibilityMaxObstruction: Float;
  public native let conversationMixCooldown: Float;
  public native let enemyPingCooldown: Float;
  public native let idleTimeBeforeAllowingOwMusicChange: Float;
  public native let drivingStreamingAmbientEmittersDistanceRolloff: Float;
  public native let lowHealthStateMaxTime: Float;
  public native let lowGearMaxTrafficSpeed: Float;
  public native let lowGearAccelerationThreshold: Float;
  public native let mediumGearMaxTrafficSpeed: Float;
  public native let mediumGearAccelerationThreshold: Float;
  public native let highGearAccelerationThreshold: Float;
}
