public native class meshMeshAppearance extends ISerializable {
  public native let name: CName;
  public native let chunkMaterials: array<CName>;
  public native let tags: array<CName>;

  public native func SetMesh(mesh: ref<CMesh>)
  public native func ResetMaterialCache()
}
