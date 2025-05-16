public native class meshMeshAppearance extends ISerializable {
  native let name: CName;
  native let chunkMaterials: array<CName>;
  native let tags: array<CName>;

  native func SetMesh(mesh: ref<CMesh>)
  native func ResetMaterialCache()
}
