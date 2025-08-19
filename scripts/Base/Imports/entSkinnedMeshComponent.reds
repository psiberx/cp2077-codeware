public native class entSkinnedMeshComponent extends entISkinTargetComponent {
  public native let mesh: ResourceAsyncRef; // raRef<CMesh>
  public native let meshAppearance: CName;
  public native let castShadows: shadowsShadowCastingMode;
  public native let castLocalShadows: shadowsShadowCastingMode;
  public native let acceptDismemberment: Bool;
  public native let chunkMask: Uint64;
  public native let renderingPlaneAnimationParam: CName;
  public native let visibilityAnimationParam: CName;
  public native let order: Uint8;
  public native let isEnabled: Bool;
  public native let LODMode: entMeshComponentLODMode;
  public native let useProxyMeshAsShadowMesh: Bool;
  public native let forcedLodDistance: entForcedLodDistance;
  public native let overrideMeshNavigationImpact: Bool;
  public native let navigationImpact: NavGenNavigationSetting;
  public native let version: Uint8;
}
