public native struct interopMaterialListDescriptor {
  native let chunksInfo: String;
  native let chunksLODInfo: String;
  native let numLayers: Uint32;
  native let isForward: Bool;
  native let isMultilayer: Bool;
  native let isLocalInstance: Bool;
  native let isTemplate: Bool;
  native let itemMaterialIndex: Uint32;
  native let materialName: String;
  native let appearanceName: String;
  native let availableMaterials: array<String>;
}
