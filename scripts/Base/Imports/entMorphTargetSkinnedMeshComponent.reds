public native class entMorphTargetSkinnedMeshComponent extends entISkinTargetComponent {
  public native let morphResource: ResourceAsyncRef; // raRef<MorphTargetMesh>
  public native let meshAppearance: CName;
  public native let castShadows: shadowsShadowCastingMode;
  public native let castLocalShadows: shadowsShadowCastingMode;
  public native let acceptDismemberment: Bool;
  public native let chunkMask: Uint64;
  public native let renderingPlaneAnimationParam: CName;
  public native let visibilityAnimationParam: CName;
  public native let isEnabled: Bool;
  public native let tags: redTagList;
  public native let version: Uint8;
}
