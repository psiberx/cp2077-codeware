public native class scneventsCameraParamsEvent extends scnSceneEvent {
  public native let cameraRef: NodeRef;
  public native let fovValue: Float;
  public native let fovWeigh: Float;
  public native let dofIntensity: Float;
  public native let dofNearBlur: Float;
  public native let dofNearFocus: Float;
  public native let dofFarBlur: Float;
  public native let dofFarFocus: Float;
  public native let useNearPlane: Bool;
  public native let useFarPlane: Bool;
  public native let isPlayerCamera: Bool;
  public native let cameraOverrideSettings: scneventsCameraOverrideSettings;
  public native let targetActor: scnPerformerId;
  public native let targetSlot: CName;
}
