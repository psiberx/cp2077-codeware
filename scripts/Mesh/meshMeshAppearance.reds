public native class meshMeshAppearance extends ISerializable {
  public native let name: CName;
  public native let chunkMaterials: array<CName>;
  public native let tags: array<CName>;

  public static native func SetMesh(self: ref<meshMeshAppearance>, mesh: ref<CMesh>)
  public static native func ResetMaterialCache(self: ref<meshMeshAppearance>)
}
