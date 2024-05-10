public native struct gamestateMachineComponentReplicatedState {
  native let componentName: CName;
  native let enabled: Bool;
  native let stateContext: gamestateMachineStateContext;
  native let enterLadderParameter: ref<LadderDescription>;
  native let exitLadderParameter: Bool;
}
