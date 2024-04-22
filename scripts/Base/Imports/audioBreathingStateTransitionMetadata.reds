public native class audioBreathingStateTransitionMetadata extends audioAudioMetadata {
  native let fromNames: array<CName>;
  native let toName: CName;
  native let transitionStateName: CName;
  native let conditionType: audioBreathingTransitionType;
  native let conditionComparator: audioBreathingTransitionComparator;
  native let value: CName;
  native let eventTags: array<audiobreathingEventTag>;
  native let isImmediate: Bool;
}
