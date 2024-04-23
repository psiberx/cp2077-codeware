public native class AICTreeNodeConditionDefinition extends AICTreeNodeCompositeDefinition {
  native let expressions: array<ref<LibTreeINodeDefinition>>;
  native let trueBranch: ref<LibTreeINodeDefinition>;
  native let falseBranch: ref<LibTreeINodeDefinition>;
  native let reevaluateOnExecution: Bool;
}
