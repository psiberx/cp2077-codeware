public native class audioLocomotionWaterSettings extends audioAudioMetadata {
  native let defaultLegVfx: ResourceAsyncRef; // raRef<CResource>
  native let locomotionStatesLegVfx: ref<audioLocomotionStateVfxDictionary>;
  native let customActionLegVfx: ref<audioLocomotionCustomActionVfxDictionary>;
  native let minSpeedToApplyImpulses: Float;
  native let minHeelDepthToApplyImpulses: Float;
  native let shallowWaterDepth: Float;
  native let intermediateWaterDepth: Float;
  native let shallowSettings: audioLocomotionWaterContextSettings;
  native let intermediateSettings: audioLocomotionWaterContextSettings;
  native let deepSettings: audioLocomotionWaterContextSettings;
  native let minHeelDepthToSpawnFallFx: Float;
  native let minDownwardSpeedForRegularFall: Float;
  native let minDownwardSpeedForFastFall: Float;
  native let regularFallVfx: ResourceAsyncRef; // raRef<CResource>
  native let regularFallEvent: CName;
  native let fastFallVfx: ResourceAsyncRef; // raRef<CResource>
  native let fastFallEvent: CName;
}
