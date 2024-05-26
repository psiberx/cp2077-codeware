public native class ExposureAreaSettings extends IAreaSettings {
  native let exposureAdaptationSpeedUp: CurveDataFloat;
  native let exposureAdaptationSpeedDown: CurveDataFloat;
  native let exposurePercentageThresholdLow: CurveDataFloat;
  native let exposurePercentageThresholdHigh: CurveDataFloat;
  native let exposureCompensation: CurveDataFloat;
  native let exposureSkyImpact: CurveDataFloat;
  native let exposureMin: CurveDataFloat;
  native let exposureMax: CurveDataFloat;
  native let exposureCenterImportance: CurveDataFloat;
  native let cameraVelocityFaloff: Float;
}
