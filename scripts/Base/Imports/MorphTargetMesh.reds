public native class MorphTargetMesh extends resStreamedResource {
  public native let baseMesh: ResourceRef; // rRef<CMesh>
  public native let targets: array<MorphTargetMeshEntry>;
  public native let boundingBox: Box;
  public native let baseTextureParamName: CName;
  public native let blob: ref<IRenderResourceBlob>;
  public native let baseMeshAppearance: CName;
  public native let baseTexture: ResourceRef; // rRef<ITexture>
}
