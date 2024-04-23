public native class ExpressionTreeCGeneralIfNodeDefinition extends ExpressionTreeCGeneralNodeDefinition {
  native let expressions: array<ref<LibTreeINodeDefinition>>;
  native let trueBranch: ref<LibTreeINodeDefinition>;
  native let falseBranch: ref<LibTreeINodeDefinition>;
}
