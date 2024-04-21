public native class scneventsVFXDurationEvent extends scnSceneEvent {
  native let effectEntry: scnEffectEntry;
  native let startAction: scneventsVFXActionType;
  native let endAction: scneventsVFXActionType;
  native let sequenceShift: Uint32;
  native let performerId: scnPerformerId;
  native let nodeRef: NodeRef;
  native let muteSound: Bool;
}
