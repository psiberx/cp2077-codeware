public native class entTriggerVOEvent extends Event {
  native let triggerBaseName: CName;
  native let triggerVariationIndex: Uint32;
  native let triggerVariationNumber: Uint32;
  native let debugInitialContext: CName;
  native let answeringEntityIDHash: Uint64;
  native let ignoreGlobalVoLimitCheck: Bool;
  native let overridingVoContext: locVoiceoverContext;
  native let overridingVoiceoverExpression: locVoiceoverExpression;
  native let overrideVoiceoverExpression: Bool;
  native let overridingVisualStyleValue: Uint8;
  native let overrideVisualStyle: Bool;
}
