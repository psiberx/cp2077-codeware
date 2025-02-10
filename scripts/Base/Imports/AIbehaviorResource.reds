@neverRef() public native class AIbehaviorResource extends CResource {
  native let root: ref<AIbehaviorTreeNodeDefinition>;
  native let arguments: AITreeArgumentsDefinition;
  native let delegate: ref<BehaviorDelegate>;
  native let initializationEvents: array<CName>;
}

