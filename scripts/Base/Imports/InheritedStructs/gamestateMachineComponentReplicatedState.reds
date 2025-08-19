public native struct gamestateMachineComponentReplicatedState {
  public native let componentName: CName;
  public native let enabled: Bool;
  public native let stateContext: gamestateMachineStateContext;
  public native let enterLadderParameter: ref<LadderDescription>;
  public native let exitLadderParameter: Bool;
}
