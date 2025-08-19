public native class SSAOAreaSettings extends IAreaSettings {
  public native let noiseFilterTolerance: CurveDataFloat;
  public native let blurTolerance: CurveDataFloat;
  public native let upsampleTolerance: CurveDataFloat;
  public native let rejectionFalloff: CurveDataFloat;
  public native let combineResolutionsBeforeBlur: Bool;
  public native let combineResolutionsWithMul: Bool;
  public native let normalsEnable: Bool;
  public native let hierarchyDepth: Int32;
  public native let normalAOMultiply: CurveDataFloat;
  public native let normalBackProjectTolerance: CurveDataFloat;
  public native let qualityLevel: ESSAOQualityLevel;
  public native let coneAoDiffuseStrength: CurveDataFloat;
  public native let coneAoSpecularStrength: CurveDataFloat;
  public native let coneAoSpecularTreshold: CurveDataFloat;
  public native let lightAoDiffuseStrength: CurveDataFloat;
  public native let lightAoSpecularStrength: CurveDataFloat;
  public native let foliageDimDiffuse: CurveDataFloat;
  public native let foliageDimSpecular: CurveDataFloat;
}
