public native struct Multilayer_Layer {
  public native let matTile: Float;
  public native let mbTile: Float;
  public native let microblend: ResourceRef; // rRef<CBitmapTexture>
  public native let microblendContrast: Float;
  public native let microblendNormalStrength: Float;
  public native let microblendOffsetU: Float;
  public native let microblendOffsetV: Float;
  public native let opacity: Float;
  public native let offsetU: Float;
  public native let offsetV: Float;
  public native let material: ResourceRef; // rRef<Multilayer_LayerTemplate>
  public native let colorScale: CName;
  public native let normalStrength: CName;
  public native let roughLevelsIn: CName;
  public native let roughLevelsOut: CName;
  public native let metalLevelsIn: CName;
  public native let metalLevelsOut: CName;
  public native let overrides: CName;
}
