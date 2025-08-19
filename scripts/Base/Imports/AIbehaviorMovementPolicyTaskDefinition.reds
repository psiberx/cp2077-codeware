public native class AIbehaviorMovementPolicyTaskDefinition extends AIbehaviorTaskDefinition {
  public native let useCurrentPolicy: Bool;
  public native let waitForPolicy: Bool;
  public native let stopWhenDestinationReached: ref<AIArgumentMapping>;
  public native let policies: array<ref<AIbehaviorMovementPolicyTaskItemDefinition>>;
}
