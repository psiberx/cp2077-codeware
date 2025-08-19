public native class AIbehaviorCommandConditionDefinition extends AIbehaviorConditionDefinition {
  public native let commandName: ref<AIArgumentMapping>;
  public native let useInheritance: Bool;
  public native let isWaiting: Bool;
  public native let isExecuting: Bool;
  public native let commandOut: ref<AIArgumentMapping>;
}
