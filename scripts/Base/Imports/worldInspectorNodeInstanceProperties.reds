public native class worldInspectorNodeInstanceProperties extends ISerializable {
  public native let setupInfo: worldCompiledNodeInstanceSetupInfo;
  public native let meshNode: ref<worldMeshNode>;
  public native let instancedMeshNode: ref<worldInstancedMeshNode>;
  public native let lastObserverDistanceToStreamingPoint: Float;
  public native let lastObserverDistanceToSecondaryReferencePoint: Float;
  public native let renderProxyAddressForDebug: Uint64;
}
