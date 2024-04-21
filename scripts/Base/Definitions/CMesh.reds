public native class CMesh extends resStreamedResource {
  native let boundingBox: Box;
  native let surfaceAreaPerAxis: Vector3;
  native let materialEntries: array<CMeshMaterialEntry>;
  native let externalMaterials: array<ResourceAsyncRef>;
  native let localMaterialBuffer: meshMeshMaterialBuffer;
  native let preloadExternalMaterials: array<ResourceRef>;
  native let inplaceResources: array<ResourceRef>;
  native let objectType: ERenderObjectType;
  native let lodLevelInfo: array<Float>;
  native let floatTrackNames: array<CName>;
  native let boneNames: array<CName>;
  native let boneRigMatrices: array<Matrix>;
  native let boneVertexEpsilons: array<Float>;
  native let lodBoneMask: array<Uint8>;
  native let constrainAutoHideDistanceToTerrainHeightMap: Bool;
  native let forceLoadAllAppearances: Bool;
  native let castGlobalShadowsCachedInCook: Bool;
  native let castLocalShadowsCachedInCook: Bool;
  native let useRayTracingShadowLODBias: Bool;
  native let castsRayTracedShadowsFromOriginalGeometry: Bool;
  native let isShadowMesh: Bool;
  native let isPlayerShadowMesh: Bool;
}
