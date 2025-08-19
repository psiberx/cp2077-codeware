public native class gameStatusEffectComponentPS extends GameComponentPS {
  // public native persistent let statusEffectArray: array<StatusEffect>;
  public native persistent let delayedFunctions: ref<gameDelayedFunctionsScheduler>;
  public native persistent let delayedFunctionsNoTd: ref<gameDelayedFunctionsScheduler>;
  public native persistent let isPlayerControlled: Bool;
  public native persistent let tickComponent: Bool;
}
