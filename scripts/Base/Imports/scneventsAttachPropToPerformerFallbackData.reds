public native struct scneventsAttachPropToPerformerFallbackData {
  public native let owner: scnPerformerId;
  public native let fallbackCachedBones: [scneventsAttachPropToPerformerCachedFallbackBone; 3];
  public native let fallbackAnimset: ResourceRef; // rRef<animAnimSet>
  public native let fallbackAnimationName: CName;
  public native let fallbackAnimTime: Float;
}
