public native class CMaterialTemplate extends IMaterialDefinition {
  public native let name: CName;
  public native let parameters: [array<ref<CMaterialParameter>>; 3];
  public native let techniques: array<MaterialTechnique>;
  public native let samplerStates: [array<SamplerStateInfo>; 3];
  public native let usedParameters: [array<MaterialUsedParameter>; 3];
  public native let materialPriority: EMaterialPriority;
  public native let materialType: ERenderMaterialType;
  public native let audioTag: CName;
  public native let resourceVersion: Uint8;
}
