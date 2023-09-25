public native class entSkinnedMeshComponent extends entISkinTargetComponent {
  native let mesh: ResourceAsyncRef;
  native let meshAppearance: CName;
  native let castShadows: shadowsShadowCastingMode;
  native let castLocalShadows: shadowsShadowCastingMode;
  native let acceptDismemberment: Bool;
  native let chunkMask: Uint64;
  native let renderingPlaneAnimationParam: CName;
  native let visibilityAnimationParam: CName;
  native let order: Uint8;
  native let isEnabled: Bool;
  native let LODMode: entMeshComponentLODMode;
  native let useProxyMeshAsShadowMesh: Bool;
  native let forcedLodDistance: entForcedLodDistance;
  native let overrideMeshNavigationImpact: Bool;
  native let navigationImpact: NavGenNavigationSetting;
}
