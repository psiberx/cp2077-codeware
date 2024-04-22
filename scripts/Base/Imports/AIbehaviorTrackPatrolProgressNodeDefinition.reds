public native class AIbehaviorTrackPatrolProgressNodeDefinition extends AIbehaviorDecoratorNodeDefinition {
  native let pathParameters: ref<AIArgumentMapping>;
  native let patrolProgress: ref<AIArgumentMapping>;
  native let startFromClosestPoint: ref<AIArgumentMapping>;
  native let patrolContinuationPolicy: ref<AIArgumentMapping>;
  native let teleportPositionAfterTimeSkipping: ref<AIArgumentMapping>;
  native let teleportRotationAfterTimeSkipping: ref<AIArgumentMapping>;
  native let handleTeleportRequest: ref<AIArgumentMapping>;
  native let fastForwardAfterTeleport: ref<AIArgumentMapping>;
}
