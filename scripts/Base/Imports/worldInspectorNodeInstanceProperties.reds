public native class worldInspectorNodeInstanceProperties extends ISerializable {
  native let setupInfo: worldCompiledNodeInstanceSetupInfo;
  native let meshNode: ref<worldMeshNode>;
  native let instancedMeshNode: ref<worldInstancedMeshNode>;
  native let lastObserverDistanceToStreamingPoint: Float;
  native let lastObserverDistanceToSecondaryReferencePoint: Float;
  native let renderProxyAddressForDebug: Uint64;
}
