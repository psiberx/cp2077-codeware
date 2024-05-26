public native class SSAOAreaSettings extends IAreaSettings {
  native let noiseFilterTolerance: CurveDataFloat;
  native let blurTolerance: CurveDataFloat;
  native let upsampleTolerance: CurveDataFloat;
  native let rejectionFalloff: CurveDataFloat;
  native let combineResolutionsBeforeBlur: Bool;
  native let combineResolutionsWithMul: Bool;
  native let normalsEnable: Bool;
  native let hierarchyDepth: Int32;
  native let normalAOMultiply: CurveDataFloat;
  native let normalBackProjectTolerance: CurveDataFloat;
  native let qualityLevel: ESSAOQualityLevel;
  native let coneAoDiffuseStrength: CurveDataFloat;
  native let coneAoSpecularStrength: CurveDataFloat;
  native let coneAoSpecularTreshold: CurveDataFloat;
  native let lightAoDiffuseStrength: CurveDataFloat;
  native let lightAoSpecularStrength: CurveDataFloat;
  native let foliageDimDiffuse: CurveDataFloat;
  native let foliageDimSpecular: CurveDataFloat;
}
