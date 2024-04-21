public native class AIbehaviorPatrolActionNodeDefinition extends AIbehaviorActionTreeNodeDefinition {
  native let path: ref<AIArgumentMapping>;
  native let patrolProgress: ref<AIArgumentMapping>;
  native let startFromClosestPoint: ref<AIArgumentMapping>;
  native let patrolContinuationPolicy: ref<AIArgumentMapping>;
  native let playStartAnimation: ref<AIArgumentMapping>;
  native let fastForwardAfterTeleport: ref<AIArgumentMapping>;
  native let workspotData: ref<AIArgumentMapping>;
  native let dependentWorkspotData: ref<AIArgumentMapping>;
  native let lookAtTarget: ref<AIArgumentMapping>;
  native let usePathContext: ref<AIArgumentMapping>;
  native let useOffMeshLinkReservation: ref<AIArgumentMapping>;
}
