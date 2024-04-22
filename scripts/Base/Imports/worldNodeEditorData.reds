public native class worldNodeEditorData extends ISerializable {
  native let id: Uint64;
  native let name: CName;
  native let globalName: String;
  native let alternativeGlobalName: String;
  native let isGlobalNameLocked: Bool;
  native let isAlternativeGlobalNameLocked: Bool;
  native let isDestructibleNode: Bool;
  native let shouldSkipStreamingInEditor: Bool;
  native let excludeOnConsole: Bool;
  native let excludeOnNextGenConsoles: Bool;
  native let proxyMeshDependency: worldProxyMeshDependencyMode;
  native let transform: worldNodeTransform;
  native let pivotTransform: Transform;
  native let variantId: Uint32;
  native let questPrefabRefHash: Uint64;
  native let isInterior: Bool;
  native let isDiscarded: Bool;
  native let isSnapTarget: Bool;
  native let isSnapSource: Bool;
  native let maxStreamingDistance: Float;
  native let initialGlobalNameHash: String;
}
