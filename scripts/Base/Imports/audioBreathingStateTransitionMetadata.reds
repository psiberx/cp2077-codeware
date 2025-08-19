@mixedRef()
public native class audioBreathingStateTransitionMetadata extends audioAudioMetadata {
  public native let fromNames: array<CName>;
  public native let toName: CName;
  public native let transitionStateName: CName;
  public native let conditionType: audioBreathingTransitionType;
  public native let conditionComparator: audioBreathingTransitionComparator;
  public native let value: CName;
  public native let eventTags: array<audiobreathingEventTag>;
  public native let isImmediate: Bool;
}
