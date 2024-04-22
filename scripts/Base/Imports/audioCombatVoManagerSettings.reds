public native class audioCombatVoManagerSettings extends audioAudioMetadata {
  native let thresholdDbForCombatDialog: Float;
  native let maxVoHearableHorizontalDistance: Float;
  native let maxVoHearableVerticalDistance: Float;
  native let maxVoVisibleDistance: Float;
  native let triggerVoEventBufferTime: Float;
  native let triggerIdleChattersTime: Float;
  native let minNoVOTimeNeededToTryPlayingGenericVO: Float;
  native let specificVoicesetVoVariationMinRepeatTime: Float;
  native let forceApucVoiceTagSelectionProbability: Float;
  native let voiceTagSelectionRandomTimeOffset: Float;
  native let genericRelaxedVOContexts: array<CName>;
  native let genericFearVOContexts: array<CName>;
  native let genericAlertedVOContexts: array<CName>;
  native let genericCombatVOContexts: array<CName>;
  native let genericCombatLosingVOContexts: array<CName>;
  native let genericCombatSingleEnemyVOContexts: array<CName>;
}
