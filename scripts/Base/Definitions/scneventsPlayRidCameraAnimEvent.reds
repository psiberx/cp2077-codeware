public native class scneventsPlayRidCameraAnimEvent extends scnSceneEvent {
  native let cameraRef: NodeRef;
  native let cameraPlacement: scneventsRidCameraPlacement;
  native let animData: scneventsPlayAnimEventData;
  native let animSRRefId: scnRidCameraAnimationSRRefId;
  native let animOriginMarker: scnMarker;
  native let activateAsGameCamera: Bool;
  native let controlRenderToTextureState: Bool;
  native let markCamerCut: Bool;
}
