public native class CMaterialInstance extends IMaterial {
  native let baseMaterial: ResourceRef; // rRef<IMaterial>
  native let enableMask: Bool;
  native let audioTag: CName;
  native let resourceVersion: Uint8;
  native let params: array<MaterialParameterInstance>;
}
