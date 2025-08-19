public native class Multilayer_LayerTemplate extends CResource {
  public native let overrides: Multilayer_LayerTemplateOverrides;
  public native let defaultOverrides: Multilayer_LayerOverrideSelection;
  public native let colorTexture: ResourceRef; // rRef<CBitmapTexture>
  public native let normalTexture: ResourceRef; // rRef<CBitmapTexture>
  public native let roughnessTexture: ResourceRef; // rRef<CBitmapTexture>
  public native let metalnessTexture: ResourceRef; // rRef<CBitmapTexture>
  public native let tilingMultiplier: Float;
  public native let colorMaskLevelsIn: [Float; 2];
  public native let colorMaskLevelsOut: [Float; 2];
}
