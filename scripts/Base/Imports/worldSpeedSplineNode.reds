public native class worldSpeedSplineNode extends worldSplineNode {
  public native let speedChangeSections: array<worldSpeedSplineNodeSpeedChangeSection>;
  public native let useDeprecated: Bool;
  public native let deprecatedSpeedRestrictions: array<worldSpeedSplineNodeSpeedRestriction>;
  public native let deprecatedDefaultSpeed: Float;
  public native let deprecatedDefaultAdjustTime: Float;
  public native let orientationChangeSections: array<worldSpeedSplineNodeOrientationChangeSection>;
  public native let roadAdjustmentFactorChangeSections: array<worldSpeedSplineNodeRoadAdjustmentFactorChangeSection>;
  public native let ignoreTerrain: Bool;
}
