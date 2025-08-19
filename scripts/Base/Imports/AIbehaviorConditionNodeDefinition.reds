public abstract native class AIbehaviorConditionNodeDefinition extends AIbehaviorDecoratorNodeDefinition {
  public native let condition: ref<AIbehaviorConditionDefinition>;
  public native let resultIfFailed: AIbehaviorCompletionStatus;
}
