public native class AIbehaviorSendSignalTaskDefinition extends AIbehaviorTaskDefinition {
  public native let signalName: CName;
  public native let startAction: gameBoolSignalAction;
  public native let startActionUserData: ref<SignalUserDataDefinition>;
  public native let endAction: gameBoolSignalAction;
  public native let endActionUserData: ref<SignalUserDataDefinition>;
}
