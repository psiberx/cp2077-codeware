@mixedRef()
public native class audioCombatVoSettings extends audioAudioMetadata {
  public native let answerGroupName: CName;
  public native let isPlayerAlly: Bool;
  public native let contexts: CName;
  public native let voTriggerVariations: CName;
  public native let generalGruntSettings: audioGeneralVoiceGruntSettings;
  public native let voTriggerLimits: audioVoiceTriggerLimits;
  public native let overridingVoTriggerLimits: CName;
  public native let barkTriggerLimits: audioVoiceTriggerLimits;
  public native let gruntTriggerLimits: audioVoiceTriggerLimits;
  public native let minDamageToInterruptVoWithPainShort: Float;
  public native let minDamageToInterruptVoWithPainLong: Float;
}
