public native class AIbehaviorMovementPolicyTaskDefinition extends AIbehaviorTaskDefinition {
  native let useCurrentPolicy: Bool;
  native let waitForPolicy: Bool;
  native let stopWhenDestinationReached: ref<AIArgumentMapping>;
  native let policies: array<ref<AIbehaviorMovementPolicyTaskItemDefinition>>;
}
