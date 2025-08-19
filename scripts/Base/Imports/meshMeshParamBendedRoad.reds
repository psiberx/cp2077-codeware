public native class meshMeshParamBendedRoad extends meshMeshParameter {
  public native let occInds: array<Uint16>;
  public native let occVerts: array<Vector4>;
  public native let occSkinWeights: array<Vector4>;
  public native let occSkinInds: array<Color>;
  public native let collInds: array<array<Uint16>>;
  public native let collVerts: array<array<Vector3>>;
  public native let collSkinWeights: array<array<Vector4>>;
  public native let collSkinInds: array<array<Color>>;
  public native let collMaterialName: array<String>;
  public native let collFilterPresetName: array<String>;
  public native let collFaceMatInds: array<array<Uint16>>;
  public native let collFaceMaterialNames: array<array<String>>;
}
