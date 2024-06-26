public native class animAnimStateMachineConditionalEntry extends ISerializable {
  native let targetStateIndex: Uint32;
  native let condition: ref<animIAnimStateTransitionCondition>;
  native let isEnabled: Bool;
  native let priority: Int32;
  native let isForcedToTrue: Bool;
}
