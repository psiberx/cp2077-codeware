public native class AIbehaviorActionDynamicMoveTreeNodeDefinition extends AIbehaviorActionTreeNodeDefinition {
  public native let moveType: ref<AIArgumentMapping>;
  public native let target: ref<AIArgumentMapping>;
  public native let targetPosition: ref<AIArgumentMapping>;
  public native let toleranceRadius: ref<AIArgumentMapping>;
  public native let desiredDistanceFromTarget: ref<AIArgumentMapping>;
  public native let strafingTarget: ref<AIArgumentMapping>;
  public native let stopWhenDestinationReached: ref<AIArgumentMapping>;
  public native let rotateEntity: ref<AIArgumentMapping>;
  public native let ignoreNavigation: ref<AIArgumentMapping>;
}
