public native class AIbehaviorSelectWorkspotNodeDefinition extends AIbehaviorDecoratorNodeDefinition {
  native let spotInstance: ref<AIArgumentMapping>;
  native let workspotData: ref<AIArgumentMapping>;
  native let dependentWorkspotData: ref<AIArgumentMapping>;
  native let repeatChild: Bool;
  native let fastForwardAfterTeleport: ref<AIArgumentMapping>;
}
