public native struct AIbehaviorNodeStatusDebuggerCommandEntry {
  native let status: AIbehaviorDebugNodeStatus;
  native let generation: Uint32;
  native let failure: ref<gamedebugFailure>;
}
