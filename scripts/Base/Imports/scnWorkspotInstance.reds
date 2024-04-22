public native struct scnWorkspotInstance {
  native let workspotInstanceId: scnSceneWorkspotInstanceId;
  native let dataId: scnSceneWorkspotDataId;
  native let localTransform: Transform;
  native let playAtActorLocation: Bool;
  native let originMarker: scnMarker;
}
