public native class meshMeshParamBendedRoad extends meshMeshParameter {
  native let occInds: array<Uint16>;
  native let occVerts: array<Vector4>;
  native let occSkinWeights: array<Vector4>;
  native let occSkinInds: array<Color>;
  native let collInds: array<array<Uint16>>;
  native let collVerts: array<array<Vector3>>;
  native let collSkinWeights: array<array<Vector4>>;
  native let collSkinInds: array<array<Color>>;
  native let collMaterialName: array<String>;
  native let collFilterPresetName: array<String>;
  native let collFaceMatInds: array<array<Uint16>>;
  native let collFaceMaterialNames: array<array<String>>;
}
