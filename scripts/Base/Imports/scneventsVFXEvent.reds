public native class scneventsVFXEvent extends scnSceneEvent {
  native let effectEntry: scnEffectEntry;
  native let action: scneventsVFXActionType;
  native let sequenceShift: Uint32;
  native let performerId: scnPerformerId;
  native let nodeRef: NodeRef;
  native let muteSound: Bool;
}
