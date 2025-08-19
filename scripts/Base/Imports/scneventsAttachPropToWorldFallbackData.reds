public native struct scneventsAttachPropToWorldFallbackData {
  public native let owner: scnPerformerId;
  public native let fallbackCachedBones: [scneventsAttachPropToWorldCachedFallbackBone; 2];
  public native let fallbackAnimset: ResourceRef; // rRef<animAnimSet>
  public native let fallbackAnimationName: CName;
  public native let fallbackAnimTime: Float;
}
