public native class AIbehaviorSendSignalTaskDefinition extends AIbehaviorTaskDefinition {
  native let signalName: CName;
  native let startAction: gameBoolSignalAction;
  native let startActionUserData: ref<SignalUserDataDefinition>;
  native let endAction: gameBoolSignalAction;
  native let endActionUserData: ref<SignalUserDataDefinition>;
}
