public native struct scneventsSpawnEntityEventParams {
  public native let performer: scnPerformerId;
  public native let referencePerformer: scnPerformerId;
  public native let referencePerformerSlotId: TweakDBID;
  public native let referencePerformerItemId: TweakDBID;
  public native let fallbackData: array<scneventsSpawnEntityEventFallbackData>;
}
