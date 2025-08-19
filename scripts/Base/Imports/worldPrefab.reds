public native class worldPrefab extends resStreamedResource {
  public native let mainGroup: ref<worldNodesGroup>;
  public native let type: worldPrefabType;
  public native let teamOwnership: worldPrefabOwnership;
  public native let streamingOcclusion: worldPrefabStreamingOcclusion;
  public native let streamingImportance: worldPrefabStreamingImportance;
  public native let defaultVariants: ref<worldPrefabVariantsList>;
  public native let isLocked: Bool;
  public native let maxBounds: Box;
  public native let environmentDefinition: ResourceAsyncRef; // raRef<worldEnvironmentDefinition>
  public native let terrainMultilayerSetup: ResourceAsyncRef; // raRef<Multilayer_Setup>
  public native let foliageBrushToTerrainLayerMapping: ResourceAsyncRef; // raRef<worldAutoFoliageMapping>
  public native let prefabUniqueId: CRUID;
  public native let metadataArray: array<ref<worldPrefabMetadata>>;
  public native let isMerged: Bool;
  public native let proxyMeshBuildParams: worldProxyMeshBuildParams;
  public native let isProxyMeshOnly: Bool;
  public native let proxyMesh: ResourceAsyncRef; // raRef<CMesh>
  public native let proxyScale: Vector3;
  public native let maxProxyStreamingDistance: Float;
  public native let proxyDistanceFactor: Float;
  public native let averageNodeDiagonal: Float;
  public native let boostInnerNodesToProxyDistance: Bool;
  public native let overrideStreamingPosWithBBoxCenter: Bool;
  public native let ignoreMeshEmbeddedOccluders: Bool;
  public native let ignoreAllOccluders: Bool;
  public native let excludeOnConsole: Bool;
  public native let excludeOnNextGenConsoles: Bool;
  public native let isTerrainPrefab: Bool;
  public native let minimapContribution: worldPrefabMinimapContribution;
  public native let interiorMapContribution: worldPrefabInteriorMapContribution;
  public native let booleanProxyHelper: ResourceAsyncRef; // raRef<worldPrefab>
  public native let proxyLimiterHelper: ResourceAsyncRef; // raRef<worldPrefab>
  public native let customProxyMeshHelper: ResourceAsyncRef; // raRef<CMesh>
}
