public native class AIbehaviorMappingExpressionDefinition extends AIbehaviorPassiveExpressionDefinition {
  public native let mapping: ref<AIArgumentMapping>;
  public native let update: Bool;
  public native let updatePeriod: Float;
  public native let behaviorCallbackNames: array<CName>;
}
