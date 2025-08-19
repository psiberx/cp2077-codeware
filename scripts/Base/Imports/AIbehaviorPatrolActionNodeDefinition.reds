public native class AIbehaviorPatrolActionNodeDefinition extends AIbehaviorActionTreeNodeDefinition {
  public native let path: ref<AIArgumentMapping>;
  public native let patrolProgress: ref<AIArgumentMapping>;
  public native let startFromClosestPoint: ref<AIArgumentMapping>;
  public native let patrolContinuationPolicy: ref<AIArgumentMapping>;
  public native let playStartAnimation: ref<AIArgumentMapping>;
  public native let fastForwardAfterTeleport: ref<AIArgumentMapping>;
  public native let workspotData: ref<AIArgumentMapping>;
  public native let dependentWorkspotData: ref<AIArgumentMapping>;
  public native let lookAtTarget: ref<AIArgumentMapping>;
  public native let usePathContext: ref<AIArgumentMapping>;
  public native let useOffMeshLinkReservation: ref<AIArgumentMapping>;
}
