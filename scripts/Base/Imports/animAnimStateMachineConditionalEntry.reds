public native class animAnimStateMachineConditionalEntry extends ISerializable {
  public native let targetStateIndex: Uint32;
  public native let condition: ref<animIAnimStateTransitionCondition>;
  public native let isEnabled: Bool;
  public native let priority: Int32;
  public native let isForcedToTrue: Bool;
}
