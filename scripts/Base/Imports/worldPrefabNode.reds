public native class worldPrefabNode extends worldNode {
  native let prefab: ResourceAsyncRef; // raRef<worldPrefab>
  native let canBeToggledInGame: Bool;
  native let noCollisions: Bool;
  native let enableRenderSceneLayerOverride: Bool;
  native let streamingImportance: worldPrefabStreamingImportance;
  native let streamingOcclusionOverride: worldPrefabStreamingOcclusion;
  native let interiorMapContribution: worldPrefabInteriorMapContribution;
  native let ignoreMeshEmbeddedOccluders: Bool;
  native let ignoreAllOccluders: Bool;
  native let occluderAutoHideDistanceScale: Uint8;
  native let proxyMeshOnly: worldPrefabProxyMeshOnly;
  native let proxyScaleOverride: Bool;
  native let proxyScale: Vector3;
  native let applyMaxStreamingDistance: Bool;
}
