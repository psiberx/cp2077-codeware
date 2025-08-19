@mixedRef()
public native class audioCombatVoManagerSettings extends audioAudioMetadata {
  public native let thresholdDbForCombatDialog: Float;
  public native let maxVoHearableHorizontalDistance: Float;
  public native let maxVoHearableVerticalDistance: Float;
  public native let maxVoVisibleDistance: Float;
  public native let triggerVoEventBufferTime: Float;
  public native let triggerIdleChattersTime: Float;
  public native let minNoVOTimeNeededToTryPlayingGenericVO: Float;
  public native let specificVoicesetVoVariationMinRepeatTime: Float;
  public native let forceApucVoiceTagSelectionProbability: Float;
  public native let voiceTagSelectionRandomTimeOffset: Float;
  public native let genericRelaxedVOContexts: array<CName>;
  public native let genericFearVOContexts: array<CName>;
  public native let genericAlertedVOContexts: array<CName>;
  public native let genericCombatVOContexts: array<CName>;
  public native let genericCombatLosingVOContexts: array<CName>;
  public native let genericCombatSingleEnemyVOContexts: array<CName>;
}
