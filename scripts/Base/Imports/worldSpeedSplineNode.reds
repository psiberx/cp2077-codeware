public native class worldSpeedSplineNode extends worldSplineNode {
  native let speedChangeSections: array<worldSpeedSplineNodeSpeedChangeSection>;
  native let useDeprecated: Bool;
  native let deprecatedSpeedRestrictions: array<worldSpeedSplineNodeSpeedRestriction>;
  native let deprecatedDefaultSpeed: Float;
  native let deprecatedDefaultAdjustTime: Float;
  native let orientationChangeSections: array<worldSpeedSplineNodeOrientationChangeSection>;
  native let roadAdjustmentFactorChangeSections: array<worldSpeedSplineNodeRoadAdjustmentFactorChangeSection>;
  native let ignoreTerrain: Bool;
}
