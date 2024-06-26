public native class audioFootwearVsMaterialMetadata extends audioAudioMetadata {
  native let footwearType: CName;
  native let skidEvent: CName;
  native let defaultFootstep: CName;
  native let locomotionStates: ref<audioLocomotionStateEventDictionary>;
  native let customActionEvents: ref<audioLocomotionCustomActionEventDictionary>;
}
