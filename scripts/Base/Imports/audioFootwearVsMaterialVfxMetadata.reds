@mixedRef()
public native class audioFootwearVsMaterialVfxMetadata extends audioAudioMetadata {
  public native let footwearType: CName;
  public native let defaultVfx: ResourceAsyncRef; // raRef<CResource>
  public native let locomotionStates: ref<audioLocomotionStateVfxDictionary>;
  public native let customActionVfx: ref<audioLocomotionCustomActionVfxDictionary>;
}
