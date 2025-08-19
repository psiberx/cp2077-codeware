public native class AIbehaviorFSMTransitionDefinition extends AIbehaviorBehaviorComponentDefinition {
  public native let inState: Uint16;
  public native let outState: Uint16;
  public native let evaluationOrder: Int32;
  public native let instantConditions: array<ref<AIbehaviorInstantConditionDefinition>>;
  public native let monitorConditions: array<ref<AIbehaviorMonitorConditionDefinition>>;
  public native let eventConditions: array<ref<AIbehaviorEventConditionDefinition>>;
  public native let passiveConditions: array<ref<AIbehaviorExpressionSocket>>;
}
