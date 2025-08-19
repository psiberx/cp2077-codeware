public native struct LookAtPartsDependency {
  public native let masterPart: CName;
  public native let slavePart: CName;
  public native let angle: Float;
  public native let speedToTargetFactor: Float;
  public native let speedToTargetByAngleCurve: CurveDataFloat;
  public native let verticalPullSpeedFactor: Float;
  public native let verticalPullSpeedByAngleCurve: CurveDataFloat;
  public native let horizontalPullSpeedFactor: Float;
  public native let horizontalPullSpeedByAngleCurve: CurveDataFloat;
  public native let pullScaleBySquareSizeFactor: Float;
  public native let pullScaleBySquareSizeCurve: CurveDataFloat;
  public native let innerSquareScale: Float;
}
