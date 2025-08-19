public native struct animMathExpressionNodeData {
  public native let expression: ref<mathExprExpression>;
  public native let floatSockets: array<animAnimMathExpressionFloatSocket>;
  public native let vectorSockets: array<animAnimMathExpressionVectorSocket>;
  public native let quaternionSockets: array<animAnimMathExpressionQuaternionSocket>;
}
