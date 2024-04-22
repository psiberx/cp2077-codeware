public native struct Multilayer_Layer {
  native let matTile: Float;
  native let mbTile: Float;
  native let microblend: ResourceRef; // rRef<CBitmapTexture>
  native let microblendContrast: Float;
  native let microblendNormalStrength: Float;
  native let microblendOffsetU: Float;
  native let microblendOffsetV: Float;
  native let opacity: Float;
  native let offsetU: Float;
  native let offsetV: Float;
  native let material: ResourceRef; // rRef<Multilayer_LayerTemplate>
  native let colorScale: CName;
  native let normalStrength: CName;
  native let roughLevelsIn: CName;
  native let roughLevelsOut: CName;
  native let metalLevelsIn: CName;
  native let metalLevelsOut: CName;
  native let overrides: CName;
}
