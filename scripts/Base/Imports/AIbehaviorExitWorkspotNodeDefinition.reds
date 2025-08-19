public native class AIbehaviorExitWorkspotNodeDefinition extends AIbehaviorDecoratorNodeDefinition {
  public native let skipExitAnimation: ref<AIArgumentMapping>;
  public native let useSlowExitAnimation: ref<AIArgumentMapping>;
  public native let doSlowIfFastExitFails: ref<AIArgumentMapping>;
  public native let stayInWorkspotIfExitFails: ref<AIArgumentMapping>;
  public native let tryBlendFastExitToWalk: ref<AIArgumentMapping>;
  public native let dontRequestExit: ref<AIArgumentMapping>;
  public native let cancelQueuedCommand: ref<AIArgumentMapping>;
  public native let target: ref<AIArgumentMapping>;
}
