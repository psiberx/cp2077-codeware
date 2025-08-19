@mixedRef()
public native class audioFootwearVsMaterialMetadata extends audioAudioMetadata {
  public native let footwearType: CName;
  public native let skidEvent: CName;
  public native let defaultFootstep: CName;
  public native let locomotionStates: ref<audioLocomotionStateEventDictionary>;
  public native let customActionEvents: ref<audioLocomotionCustomActionEventDictionary>;
}
