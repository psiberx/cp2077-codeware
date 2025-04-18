public native class AIbehaviorFSMStateDefinition extends AIbehaviorTreeNodeDefinition {
  native let behaviorRoot: ref<AIbehaviorTreeNodeDefinition>;
  native let isInitial: Bool;
  native let isExit: Bool;
  native let completionStatus: AIbehaviorStateCompletionStatus;
}
