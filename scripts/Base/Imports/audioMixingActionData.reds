public native struct audioMixingActionData {
  public native let actionType: audioMixingActionType;
  public native let voContext: locVoiceoverContext;
  public native let tagValue: CName;
  public native let dbOffset: Float;
  public native let distanceRolloffFactor: Float;
  public native let voEventOverride: CName;
  public native let customParametersSetKey: Uint64;
  public native let customParameters: array<audioAudSimpleParameter>;
}
