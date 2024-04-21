public native class audioCombatVoSettings extends audioAudioMetadata {
  native let answerGroupName: CName;
  native let isPlayerAlly: Bool;
  native let contexts: CName;
  native let voTriggerVariations: CName;
  native let generalGruntSettings: audioGeneralVoiceGruntSettings;
  native let voTriggerLimits: audioVoiceTriggerLimits;
  native let overridingVoTriggerLimits: CName;
  native let barkTriggerLimits: audioVoiceTriggerLimits;
  native let gruntTriggerLimits: audioVoiceTriggerLimits;
  native let minDamageToInterruptVoWithPainShort: Float;
  native let minDamageToInterruptVoWithPainLong: Float;
}
