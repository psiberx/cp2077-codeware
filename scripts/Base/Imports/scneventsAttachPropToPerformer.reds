public native class scneventsAttachPropToPerformer extends scnSceneEvent {
  native let propId: scnPropId;
  native let performerId: scnPerformerId;
  native let slot: CName;
  native let offsetMode: scnOffsetMode;
  native let customOffsetPos: Vector3;
  native let customOffsetRot: Quaternion;
  native let fallbackData: array<scneventsAttachPropToPerformerFallbackData>;
}
