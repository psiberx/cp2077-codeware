public native class AIbehaviorTrackPatrolProgressNodeDefinition extends AIbehaviorDecoratorNodeDefinition {
  public native let pathParameters: ref<AIArgumentMapping>;
  public native let patrolProgress: ref<AIArgumentMapping>;
  public native let startFromClosestPoint: ref<AIArgumentMapping>;
  public native let patrolContinuationPolicy: ref<AIArgumentMapping>;
  public native let teleportPositionAfterTimeSkipping: ref<AIArgumentMapping>;
  public native let teleportRotationAfterTimeSkipping: ref<AIArgumentMapping>;
  public native let handleTeleportRequest: ref<AIArgumentMapping>;
  public native let fastForwardAfterTeleport: ref<AIArgumentMapping>;
}
