public native class AIbehaviorDriveChaseTargetTreeNodeDefinition extends AIbehaviorDriveTreeNodeDefinition {
  native let target: ref<AIArgumentMapping>;
  native let distanceMin: ref<AIArgumentMapping>;
  native let distanceMax: ref<AIArgumentMapping>;
  native let forcedStartSpeed: ref<AIArgumentMapping>;
  native let needDriver: ref<AIArgumentMapping>;
  native let aggressiveRammingEnabled: ref<AIArgumentMapping>;
  native let ignoreChaseVehiclesLimit: ref<AIArgumentMapping>;
  native let boostDrivingStats: ref<AIArgumentMapping>;
}
