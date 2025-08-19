public native class worldPrefabNode extends worldNode {
  public native let prefab: ResourceAsyncRef; // raRef<worldPrefab>
  public native let instanceData: ref<worldPrefabInstanceData>;
  public native let enabledVariants: ref<worldPrefabVariantsList>;
  public native let canBeToggledInGame: Bool;
  public native let noCollisions: Bool;
  public native let enableRenderSceneLayerOverride: Bool;
  public native let streamingImportance: worldPrefabStreamingImportance;
  public native let streamingOcclusionOverride: worldPrefabStreamingOcclusion;
  public native let interiorMapContribution: worldPrefabInteriorMapContribution;
  public native let ignoreMeshEmbeddedOccluders: Bool;
  public native let ignoreAllOccluders: Bool;
  public native let occluderAutoHideDistanceScale: Uint8;
  public native let proxyMeshOnly: worldPrefabProxyMeshOnly;
  public native let proxyScaleOverride: Bool;
  public native let proxyScale: Vector3;
  public native let applyMaxStreamingDistance: Bool;
}
