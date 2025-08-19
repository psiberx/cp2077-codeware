public native class worldNodeEditorData extends ISerializable {
  public native let id: Uint64;
  public native let name: CName;
  public native let globalName: String;
  public native let alternativeGlobalName: String;
  public native let isGlobalNameLocked: Bool;
  public native let isAlternativeGlobalNameLocked: Bool;
  public native let isDestructibleNode: Bool;
  public native let shouldSkipStreamingInEditor: Bool;
  public native let excludeOnConsole: Bool;
  public native let excludeOnNextGenConsoles: Bool;
  public native let proxyMeshDependency: worldProxyMeshDependencyMode;
  public native let transform: worldNodeTransform;
  public native let pivotTransform: Transform;
  public native let variantId: Uint32;
  public native let questPrefabRefHash: Uint64;
  public native let isInterior: Bool;
  public native let isDiscarded: Bool;
  public native let isSnapTarget: Bool;
  public native let isSnapSource: Bool;
  public native let maxStreamingDistance: Float;
  public native let initialGlobalNameHash: String;
}
