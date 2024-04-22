public native class Multilayer_LayerTemplate extends CResource {
  native let overrides: Multilayer_LayerTemplateOverrides;
  native let defaultOverrides: Multilayer_LayerOverrideSelection;
  native let colorTexture: ResourceRef; // rRef<CBitmapTexture>
  native let normalTexture: ResourceRef; // rRef<CBitmapTexture>
  native let roughnessTexture: ResourceRef; // rRef<CBitmapTexture>
  native let metalnessTexture: ResourceRef; // rRef<CBitmapTexture>
  native let tilingMultiplier: Float;
}
