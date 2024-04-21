public native struct scneventsSpawnEntityEventParams {
  native let performer: scnPerformerId;
  native let referencePerformer: scnPerformerId;
  native let referencePerformerSlotId: TweakDBID;
  native let referencePerformerItemId: TweakDBID;
  native let fallbackData: array<scneventsSpawnEntityEventFallbackData>;
}
