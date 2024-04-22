public native class AIbehaviorActionDynamicMoveTreeNodeDefinition extends AIbehaviorActionTreeNodeDefinition {
  native let moveType: ref<AIArgumentMapping>;
  native let target: ref<AIArgumentMapping>;
  native let targetPosition: ref<AIArgumentMapping>;
  native let toleranceRadius: ref<AIArgumentMapping>;
  native let desiredDistanceFromTarget: ref<AIArgumentMapping>;
  native let strafingTarget: ref<AIArgumentMapping>;
  native let stopWhenDestinationReached: ref<AIArgumentMapping>;
  native let rotateEntity: ref<AIArgumentMapping>;
  native let ignoreNavigation: ref<AIArgumentMapping>;
}
