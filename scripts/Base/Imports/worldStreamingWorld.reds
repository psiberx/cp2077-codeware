public native class worldStreamingWorld extends CResource {
  public native let version: Uint32;
  public native let blockRefs: array<ResourceRef>;
  public native let environmentDefinition: ResourceRef; // rRef<worldEnvironmentDefinition>
  public native let worldBoundingBox: Box;
  public native let persistentStateData: ResourceRef; // rRef<CResource>
  public native let deviceResource: ResourceRef; // rRef<CResource>
  public native let deviceInitResource: ResourceRef; // rRef<CResource>
  public native let mappinResource: ResourceRef; // rRef<CResource>
  public native let poiMappinResource: ResourceRef; // rRef<CResource>
  public native let areaResource: ResourceRef; // rRef<CResource>
  public native let lootResource: ResourceRef; // rRef<CResource>
  public native let locationResource: ResourceRef; // rRef<CResource>
  public native let locomotionPathResource: ResourceAsyncRef; // raRef<CResource>
  public native let autoFoliageMapping: ResourceAsyncRef; // raRef<worldAutoFoliageMapping>
  public native let trafficPersistentResource: ResourceAsyncRef; // raRef<CResource>
  public native let trafficLaneConnectivityResource: ResourceAsyncRef; // raRef<CResource>
  public native let trafficLanePolygonsResource: ResourceAsyncRef; // raRef<CResource>
  public native let trafficLaneSpotsResource: ResourceAsyncRef; // raRef<CResource>
  public native let trafficSpatialRepresentationResource: ResourceAsyncRef; // raRef<CResource>
  public native let trafficCollisionResource: ResourceAsyncRef; // raRef<CResource>
  public native let trafficNullAreaCollisionResource: ResourceAsyncRef; // raRef<CResource>
  public native let smartObjectCompiledRootResource: ResourceAsyncRef; // raRef<CResource>
  public native let geometryCacheResource: ResourceRef; // rRef<CResource>
  public native let wasBuiltForSceneRecording: Bool;
  public native let streamingQueryDataResource: ResourceAsyncRef; // raRef<worldStreamingQueryDataResource>
}
