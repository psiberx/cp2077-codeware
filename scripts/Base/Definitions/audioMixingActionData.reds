public native struct audioMixingActionData {
  native let actionType: audioMixingActionType;
  native let voContext: locVoiceoverContext;
  native let tagValue: CName;
  native let dbOffset: Float;
  native let distanceRolloffFactor: Float;
  native let voEventOverride: CName;
  native let customParametersSetKey: Uint64;
  native let customParameters: array<audioAudSimpleParameter>;
}
