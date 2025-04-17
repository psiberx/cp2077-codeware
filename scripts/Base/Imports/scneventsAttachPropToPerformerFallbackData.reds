public native struct scneventsAttachPropToPerformerFallbackData {
  native let owner: scnPerformerId;
  native let fallbackCachedBones: [scneventsAttachPropToPerformerCachedFallbackBone; 3];
  native let fallbackAnimset: ResourceRef; // rRef<animAnimSet>
  native let fallbackAnimationName: CName;
  native let fallbackAnimTime: Float;
}
