public native class AIbehaviorPassiveConditionNodeDefinition extends AIbehaviorDecoratorNodeDefinition {
  native let condition: ref<AIbehaviorPassiveConditionDefinition>;
  native let resultIfFailed: AIbehaviorCompletionStatus;
}
