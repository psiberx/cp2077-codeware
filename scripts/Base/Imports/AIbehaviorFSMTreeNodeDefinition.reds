public native class AIbehaviorFSMTreeNodeDefinition extends AIbehaviorTreeNodeDefinition {
  public native let states: array<ref<AIbehaviorFSMStateDefinition>>;
  public native let transitions: array<ref<AIbehaviorFSMTransitionDefinition>>;
  public native let initialState: ref<AIbehaviorFSMStateDefinition>;
}
