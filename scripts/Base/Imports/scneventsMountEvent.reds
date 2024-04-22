public native class scneventsMountEvent extends scnSceneEvent {
  native let parent: scnPerformerId;
  native let child: scnPerformerId;
  native let slotName: CName;
  native let carryStyle: gamePSMBodyCarryingStyle;
  native let isInstant: Bool;
  native let removePitchRollRotationOnDismount: Bool;
  native let keepTransform: Bool;
  native let isCarrying: Bool;
  native let switchRenderPlane: Bool;
}
