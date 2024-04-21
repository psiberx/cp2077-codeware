public native struct LookAtPartsDependency {
  native let masterPart: CName;
  native let slavePart: CName;
  native let angle: Float;
  native let speedToTargetFactor: Float;
  native let verticalPullSpeedFactor: Float;
  native let horizontalPullSpeedFactor: Float;
  native let pullScaleBySquareSizeFactor: Float;
  native let innerSquareScale: Float;
}
