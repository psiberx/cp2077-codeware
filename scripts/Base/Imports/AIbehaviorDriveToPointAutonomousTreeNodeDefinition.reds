public native class AIbehaviorDriveToPointAutonomousTreeNodeDefinition extends AIbehaviorDriveTreeNodeDefinition {
  native let targetPosition: ref<AIArgumentMapping>;
  native let maxSpeed: ref<AIArgumentMapping>;
  native let minSpeed: ref<AIArgumentMapping>;
  native let clearTrafficOnPath: ref<AIArgumentMapping>;
  native let minimumDistanceToTarget: ref<AIArgumentMapping>;
  native let forcedStartSpeed: ref<AIArgumentMapping>;
  native let driveDownTheRoadIndefinitely: ref<AIArgumentMapping>;
}
