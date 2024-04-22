public native struct gameEffectDefinition {
  native let tag: CName;
  native let objectProviders: array<ref<EffectObjectProvider>>;
  native let objectFilters: array<ref<gameEffectObjectFilter>>;
  native let effectExecutors: array<ref<EffectExecutor>>;
  native let durationModifiers: array<ref<EffectDurationModifier>>;
  native let preActions: array<ref<EffectPreAction>>;
  native let postActions: array<ref<EffectPostAction>>;
  native let noTargetsActions: array<ref<EffectAction>>;
  native let settings: gameEffectSettings;
  native let debugSettings: gameEffectDebugSettings;
}
