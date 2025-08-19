@mixedRef()
public native class audioLocomotionWaterSettings extends audioAudioMetadata {
  public native let defaultLegVfx: ResourceAsyncRef; // raRef<CResource>
  public native let locomotionStatesLegVfx: ref<audioLocomotionStateVfxDictionary>;
  public native let customActionLegVfx: ref<audioLocomotionCustomActionVfxDictionary>;
  public native let minSpeedToApplyImpulses: Float;
  public native let minHeelDepthToApplyImpulses: Float;
  public native let shallowWaterDepth: Float;
  public native let intermediateWaterDepth: Float;
  public native let shallowSettings: audioLocomotionWaterContextSettings;
  public native let intermediateSettings: audioLocomotionWaterContextSettings;
  public native let deepSettings: audioLocomotionWaterContextSettings;
  public native let minHeelDepthToSpawnFallFx: Float;
  public native let minDownwardSpeedForRegularFall: Float;
  public native let minDownwardSpeedForFastFall: Float;
  public native let regularFallVfx: ResourceAsyncRef; // raRef<CResource>
  public native let regularFallEvent: CName;
  public native let fastFallVfx: ResourceAsyncRef; // raRef<CResource>
  public native let fastFallEvent: CName;
}
