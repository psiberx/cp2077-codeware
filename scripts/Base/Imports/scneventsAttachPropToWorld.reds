public native class scneventsAttachPropToWorld extends scnSceneEvent {
  public native let propId: scnPropId;
  public native let offsetMode: scnOffsetMode;
  public native let customOffsetPos: Vector3;
  public native let customOffsetRot: Quaternion;
  public native let referencePerformer: scnPerformerId;
  public native let referencePerformerSlotId: TweakDBID;
  public native let referencePerformerItemId: TweakDBID;
  public native let fallbackData: array<scneventsAttachPropToWorldFallbackData>;
}
