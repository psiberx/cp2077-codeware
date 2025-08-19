public native class scneventsAttachPropToPerformer extends scnSceneEvent {
  public native let propId: scnPropId;
  public native let performerId: scnPerformerId;
  public native let slot: CName;
  public native let offsetMode: scnOffsetMode;
  public native let customOffsetPos: Vector3;
  public native let customOffsetRot: Quaternion;
  public native let fallbackData: array<scneventsAttachPropToPerformerFallbackData>;
}
