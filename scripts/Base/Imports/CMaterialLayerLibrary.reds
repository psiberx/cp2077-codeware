public native class CMaterialLayerLibrary extends CResource {
  public native let uvTiling: Float;
  public native let mbTiling: Float;
  public native let microblendContrast: Float;
  public native let paletteColorIndex: Uint32;
  public native let layers: array<MaterialLayerDef>;
  public native let microblends: array<MicroblendDef>;
}
