public native class animAnimNode_StateMachine extends animAnimNode_Base {
  native let states: array<ref<animAnimNode_State>>;
  native let frozenState: ref<animAnimNode_StateFrozen>;
  native let transitions: array<ref<animAnimStateTransitionDescription>>;
  native let conditionalEntries: array<ref<animAnimStateMachineConditionalEntry>>;
  native let globalTransitions: array<ref<animAnimStateTransitionDescription>>;
  native let anyStateInterpolator: ref<animIAnimStateTransitionInterpolator>;
  native let defaultStateIndex: Uint32;
  native let notifyOnEnterState: Bool;
}
