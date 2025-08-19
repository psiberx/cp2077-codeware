public native class worldNodesGroup extends ISerializable {
  public native let name: CName;
  public native let id: Uint64;
  public native let groupUniqueId: CRUID;
  public native let nodes: array<ref<worldNode>>;
  public native let subGroups: array<ref<worldNodesGroup>>;
  public native let type: worldNodeGroupType;
  public native let keepPosition: Bool;
  public native let transform: Transform;
  public native let transformCalculated: Bool;
  public native let customPivotOffset: Transform;
  public native let proxyMeshGroupBuildParams: worldProxyMeshGroupBuildParams;
  public native let proxyMesh: ResourceAsyncRef; // raRef<CMesh>
  public native let proxyDistanceFactor: Float;
  public native let metadataArray: array<ref<worldPrefabMetadata>>;
}
