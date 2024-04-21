public native struct inkCompositionPreset {
  native let stateName: CName;
  native let useBackgroundTexture: Bool;
  native let shaderParams: fxCompositionShaderParams;
  native let transitions: array<inkCompositionTransition>;
}
