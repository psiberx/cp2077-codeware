public native class animAnimNode_StateMachine extends animAnimNode_Base {
  public native let states: array<ref<animAnimNode_State>>;
  public native let frozenState: ref<animAnimNode_StateFrozen>;
  public native let transitions: array<ref<animAnimStateTransitionDescription>>;
  public native let conditionalEntries: array<ref<animAnimStateMachineConditionalEntry>>;
  public native let globalTransitions: array<ref<animAnimStateTransitionDescription>>;
  public native let anyStateInterpolator: ref<animIAnimStateTransitionInterpolator>;
  public native let defaultStateIndex: Uint32;
  public native let notifyOnEnterState: Bool;
}
