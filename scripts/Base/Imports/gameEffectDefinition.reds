public native struct gameEffectDefinition {
  public native let tag: CName;
  public native let objectProviders: array<ref<EffectObjectProvider>>;
  public native let objectFilters: array<ref<gameEffectObjectFilter>>;
  public native let effectExecutors: array<ref<EffectExecutor>>;
  public native let durationModifiers: array<ref<EffectDurationModifier>>;
  public native let preActions: array<ref<EffectPreAction>>;
  public native let postActions: array<ref<EffectPostAction>>;
  public native let noTargetsActions: array<ref<EffectAction>>;
  public native let settings: gameEffectSettings;
  public native let debugSettings: gameEffectDebugSettings;
}
