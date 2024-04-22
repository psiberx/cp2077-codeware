public native class AIbehaviorExitWorkspotNodeDefinition extends AIbehaviorDecoratorNodeDefinition {
  native let skipExitAnimation: ref<AIArgumentMapping>;
  native let useSlowExitAnimation: ref<AIArgumentMapping>;
  native let doSlowIfFastExitFails: ref<AIArgumentMapping>;
  native let stayInWorkspotIfExitFails: ref<AIArgumentMapping>;
  native let tryBlendFastExitToWalk: ref<AIArgumentMapping>;
  native let dontRequestExit: ref<AIArgumentMapping>;
  native let cancelQueuedCommand: ref<AIArgumentMapping>;
  native let target: ref<AIArgumentMapping>;
}
