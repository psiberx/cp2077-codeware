public native struct MaterialTechnique {
  public native let passes: array<MaterialPass>;
  public native let featureFlagsEnabledMask: FeatureFlagsMask;
  public native let streamsToBind: Uint32;
}
