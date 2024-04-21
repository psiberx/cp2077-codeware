public native class AIbehaviorCommandConditionDefinition extends AIbehaviorConditionDefinition {
  native let commandName: ref<AIArgumentMapping>;
  native let useInheritance: Bool;
  native let isWaiting: Bool;
  native let isExecuting: Bool;
  native let commandOut: ref<AIArgumentMapping>;
}
