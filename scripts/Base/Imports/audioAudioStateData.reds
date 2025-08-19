public native struct audioAudioStateData {
  public native let stateName: CName;
  public native let enterEvent: CName;
  public native let exitEvent: CName;
  public native let exitTransitions: array<audioAudioStateTransitionData>;
  public native let mixingActions: array<audioMixingActionData>;
  public native let interruptionSources: array<CName>;
  public native let writeVariableActions: array<audioAudioSceneVariableWriteActionData>;
}
