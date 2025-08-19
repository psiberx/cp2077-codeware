public native class scneventsMountEvent extends scnSceneEvent {
  public native let parent: scnPerformerId;
  public native let child: scnPerformerId;
  public native let slotName: CName;
  public native let carryStyle: gamePSMBodyCarryingStyle;
  public native let isInstant: Bool;
  public native let removePitchRollRotationOnDismount: Bool;
  public native let keepTransform: Bool;
  public native let isCarrying: Bool;
  public native let switchRenderPlane: Bool;
}
