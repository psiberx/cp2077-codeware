public abstract native class AIbehaviorDistanceToTargetConditionDefinition extends AIbehaviorConditionDefinition {
  public native let target: ref<AIArgumentMapping>;
  public native let distance: ref<AIArgumentMapping>;
  public native let comparisonOperator: EComparisonType;
}
