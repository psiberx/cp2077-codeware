public native class gameStatusEffectComponentPS extends GameComponentPS {
  native persistent let delayedFunctions: ref<gameDelayedFunctionsScheduler>;
  native persistent let delayedFunctionsNoTd: ref<gameDelayedFunctionsScheduler>;
  native persistent let isPlayerControlled: Bool;
  native persistent let tickComponent: Bool;
}
