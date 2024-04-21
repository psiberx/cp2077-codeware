public native struct MaterialLayerDef {
  native let name: CName;
  native let size: Uint32;
  native let colorPalette: array<Color>;
  native let material: ResourceRef; // rRef<CMaterialInstance>
}
