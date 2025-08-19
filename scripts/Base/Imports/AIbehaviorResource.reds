public native class AIbehaviorResource extends CResource {
  public native let root: ref<AIbehaviorTreeNodeDefinition>;
  public native let arguments: AITreeArgumentsDefinition;
  public native let delegate: ref<BehaviorDelegate>;
  public native let initializationEvents: array<CName>;
}
