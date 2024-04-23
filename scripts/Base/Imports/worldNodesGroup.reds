public native class worldNodesGroup extends ISerializable {
  native let name: CName;
  native let id: Uint64;
  native let groupUniqueId: CRUID;
  native let nodes: array<ref<worldNode>>;
  native let subGroups: array<ref<worldNodesGroup>>;
  native let type: worldNodeGroupType;
  native let keepPosition: Bool;
  native let transform: Transform;
  native let transformCalculated: Bool;
  native let customPivotOffset: Transform;
  native let proxyMeshGroupBuildParams: worldProxyMeshGroupBuildParams;
  native let proxyMesh: ResourceAsyncRef; // raRef<CMesh>
  native let proxyDistanceFactor: Float;
  native let metadataArray: array<ref<worldPrefabMetadata>>;
}
