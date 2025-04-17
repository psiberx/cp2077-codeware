public native struct scneventsAttachPropToWorldFallbackData {
  native let owner: scnPerformerId;
  native let fallbackCachedBones: [scneventsAttachPropToWorldCachedFallbackBone; 2];
  native let fallbackAnimset: ResourceRef; // rRef<animAnimSet>
  native let fallbackAnimationName: CName;
  native let fallbackAnimTime: Float;
}
