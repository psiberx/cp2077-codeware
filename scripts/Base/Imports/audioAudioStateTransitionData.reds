public native struct audioAudioStateTransitionData {
  public native let targetStateId: Uint8;
  public native let allConditionsFulfilled: Bool;
  public native let transitionTime: Float;
  public native let exitTime: Float;
  public native let exitSignal: CName;
  public native let readVariableActions: array<audioAudioSceneVariableReadActionData>;
  public native let conditions: array<CName>;
}
