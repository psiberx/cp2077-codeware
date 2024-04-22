public native struct audioAudioStateData {
  native let stateName: CName;
  native let enterEvent: CName;
  native let exitEvent: CName;
  native let exitTransitions: array<audioAudioStateTransitionData>;
  native let mixingActions: array<audioMixingActionData>;
  native let interruptionSources: array<CName>;
  native let writeVariableActions: array<audioAudioSceneVariableWriteActionData>;
}
