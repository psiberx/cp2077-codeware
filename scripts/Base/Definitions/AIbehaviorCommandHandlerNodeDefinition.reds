public native class AIbehaviorCommandHandlerNodeDefinition extends AIbehaviorDecoratorNodeDefinition {
  native let commandName: CName;
  native let useInheritance: Bool;
  native let contexts: array<AICommandContextsType>;
  native let commandOut: ref<AIArgumentMapping>;
  native let runningSignal: CName;
  native let waitForCommand: Bool;
  native let retryIfCommandEnqueued: Bool;
  native let resultIfNoCommand: AIbehaviorCompletionStatus;
  native let resultIfChildFailed: AIbehaviorCompletionStatus;
}
