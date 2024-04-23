public native struct animMathExpressionNodeData {
  native let expression: ref<mathExprExpression>;
  native let floatSockets: array<animAnimMathExpressionFloatSocket>;
  native let vectorSockets: array<animAnimMathExpressionVectorSocket>;
  native let quaternionSockets: array<animAnimMathExpressionQuaternionSocket>;
}
