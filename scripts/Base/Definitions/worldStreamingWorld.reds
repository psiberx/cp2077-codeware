public native class worldStreamingWorld extends CResource {
  native let version: Uint32;
  native let blockRefs: array<ResourceRef>;
  native let environmentDefinition: ResourceRef; // rRef<worldEnvironmentDefinition>
  native let worldBoundingBox: Box;
  native let persistentStateData: ResourceRef; // rRef<CResource>
  native let deviceResource: ResourceRef; // rRef<CResource>
  native let deviceInitResource: ResourceRef; // rRef<CResource>
  native let mappinResource: ResourceRef; // rRef<CResource>
  native let poiMappinResource: ResourceRef; // rRef<CResource>
  native let areaResource: ResourceRef; // rRef<CResource>
  native let lootResource: ResourceRef; // rRef<CResource>
  native let locationResource: ResourceRef; // rRef<CResource>
  native let locomotionPathResource: ResourceAsyncRef; // raRef<CResource>
  native let autoFoliageMapping: ResourceAsyncRef; // raRef<worldAutoFoliageMapping>
  native let trafficPersistentResource: ResourceAsyncRef; // raRef<CResource>
  native let trafficLaneConnectivityResource: ResourceAsyncRef; // raRef<CResource>
  native let trafficLanePolygonsResource: ResourceAsyncRef; // raRef<CResource>
  native let trafficLaneSpotsResource: ResourceAsyncRef; // raRef<CResource>
  native let trafficSpatialRepresentationResource: ResourceAsyncRef; // raRef<CResource>
  native let trafficCollisionResource: ResourceAsyncRef; // raRef<CResource>
  native let trafficNullAreaCollisionResource: ResourceAsyncRef; // raRef<CResource>
  native let smartObjectCompiledRootResource: ResourceAsyncRef; // raRef<CResource>
  native let geometryCacheResource: ResourceRef; // rRef<CResource>
  native let wasBuiltForSceneRecording: Bool;
  native let streamingQueryDataResource: ResourceAsyncRef; // raRef<worldStreamingQueryDataResource>
}
