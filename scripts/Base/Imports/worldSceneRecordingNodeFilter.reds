public native struct worldSceneRecordingNodeFilter {
  native let streamInNodesWithStreamingDistanceMoreThan: Float;
  native let streamOutPrefabProxyMeshesWithStreamingDistanceMoreThan: Float;
  native let meshNodesOnly: Bool;
  native let meshResourceFilter: worldSceneRecordingNodeMeshResourceFilter;
}
