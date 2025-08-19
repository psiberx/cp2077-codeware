public native class scneventsPlayRidCameraAnimEvent extends scnSceneEvent {
  public native let cameraRef: NodeRef;
  public native let cameraPlacement: scneventsRidCameraPlacement;
  public native let animData: scneventsPlayAnimEventData;
  public native let animSRRefId: scnRidCameraAnimationSRRefId;
  public native let animOriginMarker: scnMarker;
  public native let activateAsGameCamera: Bool;
  public native let controlRenderToTextureState: Bool;
  public native let markCamerCut: Bool;
}
