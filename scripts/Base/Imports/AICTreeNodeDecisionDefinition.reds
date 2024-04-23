public native class AICTreeNodeDecisionDefinition extends AICTreeNodeCompositeDefinition {
  native let child: ref<LibTreeINodeDefinition>;
  native let expressions: array<ref<LibTreeINodeDefinition>>;
  native let interruption: AIInterruptionSignal;
}
