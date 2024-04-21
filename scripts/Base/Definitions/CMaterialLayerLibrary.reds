public native class CMaterialLayerLibrary extends CResource {
  native let uvTiling: Float;
  native let mbTiling: Float;
  native let microblendContrast: Float;
  native let paletteColorIndex: Uint32;
  native let layers: array<MaterialLayerDef>;
  native let microblends: array<MicroblendDef>;
}
