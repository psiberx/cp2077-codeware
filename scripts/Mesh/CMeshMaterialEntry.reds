public native struct CMeshMaterialEntry {
  native let name: CName;
  native let index: Uint16;
  native let isLocalInstance: Bool;
  native let material: wref<IMaterial>;
}
