public native class AICTreeNodeDecisionDefinition extends AICTreeNodeCompositeDefinition {
  public native let child: ref<LibTreeINodeDefinition>;
  public native let expressions: array<ref<LibTreeINodeDefinition>>;
  public native let interruption: AIInterruptionSignal;
}
