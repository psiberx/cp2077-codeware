public native class questLogicalCondition extends questCondition {
  native let operation: questLogicalOperation;
  native let conditions: array<ref<questIBaseCondition>>;
}
