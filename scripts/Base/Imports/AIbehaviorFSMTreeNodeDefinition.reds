public native class AIbehaviorFSMTreeNodeDefinition extends AIbehaviorTreeNodeDefinition {
  native let states: array<ref<AIbehaviorFSMStateDefinition>>;
  native let transitions: array<ref<AIbehaviorFSMTransitionDefinition>>;
  native let initialState: ref<AIbehaviorFSMStateDefinition>;
}
