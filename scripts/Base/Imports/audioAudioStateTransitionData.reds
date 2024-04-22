public native struct audioAudioStateTransitionData {
  native let targetStateId: Uint8;
  native let allConditionsFulfilled: Bool;
  native let transitionTime: Float;
  native let exitTime: Float;
  native let exitSignal: CName;
  native let readVariableActions: array<audioAudioSceneVariableReadActionData>;
  native let conditions: array<CName>;
}
