@neverRef() public native class MorphTargetMesh extends resStreamedResource {
  native let baseMesh: ResourceRef; // rRef<CMesh>
  native let targets: array<MorphTargetMeshEntry>;
  native let boundingBox: Box;
  native let baseTextureParamName: CName;
  native let blob: ref<IRenderResourceBlob>;
  native let baseMeshAppearance: CName;
  native let baseTexture: ResourceRef; // rRef<ITexture>
}

