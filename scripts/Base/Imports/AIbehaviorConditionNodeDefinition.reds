public abstract native class AIbehaviorConditionNodeDefinition extends AIbehaviorDecoratorNodeDefinition {
  native let condition: ref<AIbehaviorConditionDefinition>;
  native let resultIfFailed: AIbehaviorCompletionStatus;
}
