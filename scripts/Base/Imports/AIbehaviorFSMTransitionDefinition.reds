public native class AIbehaviorFSMTransitionDefinition extends AIbehaviorBehaviorComponentDefinition {
  native let inState: Uint16;
  native let outState: Uint16;
  native let evaluationOrder: Int32;
  native let instantConditions: array<ref<AIbehaviorInstantConditionDefinition>>;
  native let monitorConditions: array<ref<AIbehaviorMonitorConditionDefinition>>;
  native let eventConditions: array<ref<AIbehaviorEventConditionDefinition>>;
  native let passiveConditions: array<ref<AIbehaviorExpressionSocket>>;
}
