public native class audioFootwearVsMaterialVfxMetadata extends audioAudioMetadata {
  native let footwearType: CName;
  native let defaultVfx: ResourceAsyncRef; // raRef<CResource>
  native let locomotionStates: ref<audioLocomotionStateVfxDictionary>;
  native let customActionVfx: ref<audioLocomotionCustomActionVfxDictionary>;
}
