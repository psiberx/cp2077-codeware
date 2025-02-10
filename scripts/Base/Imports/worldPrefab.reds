@neverRef() public native class worldPrefab extends resStreamedResource {
  native let mainGroup: ref<worldNodesGroup>;
  native let type: worldPrefabType;
  native let teamOwnership: worldPrefabOwnership;
  native let streamingOcclusion: worldPrefabStreamingOcclusion;
  native let streamingImportance: worldPrefabStreamingImportance;
  native let defaultVariants: ref<worldPrefabVariantsList>;
  native let isLocked: Bool;
  native let maxBounds: Box;
  native let environmentDefinition: ResourceAsyncRef; // raRef<worldEnvironmentDefinition>
  native let terrainMultilayerSetup: ResourceAsyncRef; // raRef<Multilayer_Setup>
  native let foliageBrushToTerrainLayerMapping: ResourceAsyncRef; // raRef<worldAutoFoliageMapping>
  native let prefabUniqueId: CRUID;
  native let metadataArray: array<ref<worldPrefabMetadata>>;
  native let isMerged: Bool;
  native let proxyMeshBuildParams: worldProxyMeshBuildParams;
  native let isProxyMeshOnly: Bool;
  native let proxyMesh: ResourceAsyncRef; // raRef<CMesh>
  native let proxyScale: Vector3;
  native let maxProxyStreamingDistance: Float;
  native let proxyDistanceFactor: Float;
  native let averageNodeDiagonal: Float;
  native let boostInnerNodesToProxyDistance: Bool;
  native let overrideStreamingPosWithBBoxCenter: Bool;
  native let ignoreMeshEmbeddedOccluders: Bool;
  native let ignoreAllOccluders: Bool;
  native let excludeOnConsole: Bool;
  native let excludeOnNextGenConsoles: Bool;
  native let isTerrainPrefab: Bool;
  native let minimapContribution: worldPrefabMinimapContribution;
  native let interiorMapContribution: worldPrefabInteriorMapContribution;
  native let booleanProxyHelper: ResourceAsyncRef; // raRef<worldPrefab>
  native let proxyLimiterHelper: ResourceAsyncRef; // raRef<worldPrefab>
  native let customProxyMeshHelper: ResourceAsyncRef; // raRef<CMesh>
}

