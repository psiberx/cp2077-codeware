public native struct MaterialTechnique {
  native let passes: array<MaterialPass>;
  native let featureFlagsEnabledMask: FeatureFlagsMask;
  native let streamsToBind: Uint32;
}
