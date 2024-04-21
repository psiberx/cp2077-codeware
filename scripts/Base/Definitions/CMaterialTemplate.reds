public native class CMaterialTemplate extends IMaterialDefinition {
  native let name: CName;
  native let techniques: array<MaterialTechnique>;
  native let materialPriority: EMaterialPriority;
  native let materialType: ERenderMaterialType;
  native let audioTag: CName;
  native let resourceVersion: Uint8;
}
