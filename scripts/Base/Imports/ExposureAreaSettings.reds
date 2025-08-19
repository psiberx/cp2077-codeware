public native class ExposureAreaSettings extends IAreaSettings {
  public native let exposureAdaptationSpeedUp: CurveDataFloat;
  public native let exposureAdaptationSpeedDown: CurveDataFloat;
  public native let exposurePercentageThresholdLow: CurveDataFloat;
  public native let exposurePercentageThresholdHigh: CurveDataFloat;
  public native let exposureCompensation: CurveDataFloat;
  public native let exposureSkyImpact: CurveDataFloat;
  public native let exposureMin: CurveDataFloat;
  public native let exposureMax: CurveDataFloat;
  public native let exposureCenterImportance: CurveDataFloat;
  public native let cameraVelocityFaloff: Float;
  public native let exposureCompensationOffset: Float;
}
