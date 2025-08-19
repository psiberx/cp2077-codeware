public native class effectTrackItemSound extends effectTrackItem {
  public native let eventName: CName;
  public native let switches: array<audioAudSwitch>;
  public native let params: array<audioAudParameter>;
  public native let positionName: CName;
  public native let emitterMetadataName: CName;
  public native let rtpcName: CName;
  public native let rtpcValue: ref<IEvaluatorFloat>;
}
