public native class AIbehaviorCommandHandlerNodeDefinition extends AIbehaviorDecoratorNodeDefinition {
  public native let commandName: CName;
  public native let useInheritance: Bool;
  public native let contexts: array<AICommandContextsType>;
  public native let commandOut: ref<AIArgumentMapping>;
  public native let runningSignal: CName;
  public native let waitForCommand: Bool;
  public native let retryIfCommandEnqueued: Bool;
  public native let resultIfNoCommand: AIbehaviorCompletionStatus;
  public native let resultIfChildFailed: AIbehaviorCompletionStatus;
}
