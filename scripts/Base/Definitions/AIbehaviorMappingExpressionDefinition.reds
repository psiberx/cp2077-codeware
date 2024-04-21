public native class AIbehaviorMappingExpressionDefinition extends AIbehaviorPassiveExpressionDefinition {
  native let mapping: ref<AIArgumentMapping>;
  native let update: Bool;
  native let updatePeriod: Float;
  native let behaviorCallbackNames: array<CName>;
}
