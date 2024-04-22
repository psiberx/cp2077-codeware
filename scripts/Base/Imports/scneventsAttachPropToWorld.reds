public native class scneventsAttachPropToWorld extends scnSceneEvent {
  native let propId: scnPropId;
  native let offsetMode: scnOffsetMode;
  native let customOffsetPos: Vector3;
  native let customOffsetRot: Quaternion;
  native let referencePerformer: scnPerformerId;
  native let referencePerformerSlotId: TweakDBID;
  native let referencePerformerItemId: TweakDBID;
  native let fallbackData: array<scneventsAttachPropToWorldFallbackData>;
}
