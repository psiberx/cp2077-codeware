public native class scneventsCameraParamsEvent extends scnSceneEvent {
  native let cameraRef: NodeRef;
  native let fovValue: Float;
  native let fovWeigh: Float;
  native let dofIntensity: Float;
  native let dofNearBlur: Float;
  native let dofNearFocus: Float;
  native let dofFarBlur: Float;
  native let dofFarFocus: Float;
  native let useNearPlane: Bool;
  native let useFarPlane: Bool;
  native let isPlayerCamera: Bool;
  native let cameraOverrideSettings: scneventsCameraOverrideSettings;
  native let targetActor: scnPerformerId;
  native let targetSlot: CName;
}
