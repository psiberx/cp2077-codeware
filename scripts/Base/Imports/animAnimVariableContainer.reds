public native class animAnimVariableContainer extends ISerializable {
  native let boolVariables: array<ref<animAnimVariableBool>>;
  native let intVariables: array<ref<animAnimVariableInt>>;
  native let floatVariables: array<ref<animAnimVariableFloat>>;
  native let vectorVariables: array<ref<animAnimVariableVector>>;
  native let quaternionVariables: array<ref<animAnimVariableQuaternion>>;
  native let transformVariables: array<ref<animAnimVariableTransform>>;
}
