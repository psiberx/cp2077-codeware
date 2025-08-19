public native class AIbehaviorFSMStateDefinition extends AIbehaviorTreeNodeDefinition {
  public native let behaviorRoot: ref<AIbehaviorTreeNodeDefinition>;
  public native let isInitial: Bool;
  public native let isExit: Bool;
  public native let completionStatus: AIbehaviorStateCompletionStatus;
}
