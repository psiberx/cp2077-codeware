public native struct LookAtPartsDependency {
  native let masterPart: CName;
  native let slavePart: CName;
  native let angle: Float;
  native let speedToTargetFactor: Float;
  native let speedToTargetByAngleCurve: CurveDataFloat;
  native let verticalPullSpeedFactor: Float;
  native let verticalPullSpeedByAngleCurve: CurveDataFloat;
  native let horizontalPullSpeedFactor: Float;
  native let horizontalPullSpeedByAngleCurve: CurveDataFloat;
  native let pullScaleBySquareSizeFactor: Float;
  native let pullScaleBySquareSizeCurve: CurveDataFloat;
  native let innerSquareScale: Float;
}
