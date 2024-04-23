public native class AIbehaviorNaryOperatorExpressionDefinition extends AIbehaviorPassiveExpressionDefinition {
  native let operator: AIbehaviorNaryExpressionOperators;
  native let operands: array<ref<AIbehaviorExpressionSocket>>;
}
