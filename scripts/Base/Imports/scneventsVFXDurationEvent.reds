public native class scneventsVFXDurationEvent extends scnSceneEvent {
  public native let effectEntry: scnEffectEntry;
  public native let startAction: scneventsVFXActionType;
  public native let endAction: scneventsVFXActionType;
  public native let sequenceShift: Uint32;
  public native let performerId: scnPerformerId;
  public native let nodeRef: NodeRef;
  public native let muteSound: Bool;
}
