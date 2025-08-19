public native struct MaterialLayerDef {
  public native let name: CName;
  public native let size: Uint32;
  public native let colorPalette: array<Color>;
  public native let material: ResourceRef; // rRef<CMaterialInstance>
}
