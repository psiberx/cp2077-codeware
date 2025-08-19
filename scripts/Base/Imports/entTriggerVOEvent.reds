public native class entTriggerVOEvent extends Event {
  public native let triggerBaseName: CName;
  public native let triggerVariationIndex: Uint32;
  public native let triggerVariationNumber: Uint32;
  public native let debugInitialContext: CName;
  public native let answeringEntityIDHash: Uint64;
  public native let ignoreGlobalVoLimitCheck: Bool;
  public native let overridingVoContext: locVoiceoverContext;
  public native let overridingVoiceoverExpression: locVoiceoverExpression;
  public native let overrideVoiceoverExpression: Bool;
  public native let overridingVisualStyleValue: Uint8;
  public native let overrideVisualStyle: Bool;
}
