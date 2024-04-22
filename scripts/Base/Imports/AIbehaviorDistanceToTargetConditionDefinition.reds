public abstract native class AIbehaviorDistanceToTargetConditionDefinition extends AIbehaviorConditionDefinition {
  native let target: ref<AIArgumentMapping>;
  native let distance: ref<AIArgumentMapping>;
  native let comparisonOperator: EComparisonType;
}
