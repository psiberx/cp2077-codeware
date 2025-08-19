public native class AIbehaviorSelectWorkspotNodeDefinition extends AIbehaviorDecoratorNodeDefinition {
  public native let spotInstance: ref<AIArgumentMapping>;
  public native let workspotData: ref<AIArgumentMapping>;
  public native let dependentWorkspotData: ref<AIArgumentMapping>;
  public native let repeatChild: Bool;
  public native let fastForwardAfterTeleport: ref<AIArgumentMapping>;
}
