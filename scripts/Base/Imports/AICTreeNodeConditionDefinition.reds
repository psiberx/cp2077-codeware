public native class AICTreeNodeConditionDefinition extends AICTreeNodeCompositeDefinition {
  public native let expressions: array<ref<LibTreeINodeDefinition>>;
  public native let trueBranch: ref<LibTreeINodeDefinition>;
  public native let falseBranch: ref<LibTreeINodeDefinition>;
  public native let reevaluateOnExecution: Bool;
}
