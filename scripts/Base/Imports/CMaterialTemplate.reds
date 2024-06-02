public native class CMaterialTemplate extends IMaterialDefinition {
  native let name: CName;
  native let parameters: [array<ref<CMaterialParameter>>; 3];
  native let techniques: array<MaterialTechnique>;
  native let samplerStates: [array<SamplerStateInfo>; 3];
  native let usedParameters: [array<MaterialUsedParameter>; 3];
  native let materialPriority: EMaterialPriority;
  native let materialType: ERenderMaterialType;
  native let audioTag: CName;
  native let resourceVersion: Uint8;
}
