public native class AIbehaviorDriveFollowTargetTreeNodeDefinition extends AIbehaviorDriveTreeNodeDefinition {
  native let useKinematic: ref<AIArgumentMapping>;
  native let needDriver: ref<AIArgumentMapping>;
  native let target: ref<AIArgumentMapping>;
  native let secureTimeOut: ref<AIArgumentMapping>;
  native let distanceMin: ref<AIArgumentMapping>;
  native let distanceMax: ref<AIArgumentMapping>;
  native let isPlayer: ref<AIArgumentMapping>;
  native let stopHasReachedTarget: ref<AIArgumentMapping>;
  native let useTraffic: ref<AIArgumentMapping>;
  native let allowStubMovement: ref<AIArgumentMapping>;
}
