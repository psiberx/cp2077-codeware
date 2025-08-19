public native struct scneventsSpawnEntityEventFallbackData {
  public native let owner: scnPerformerId;
  public native let fallbackCachedBones: [scneventsSpawnEntityEventCachedFallbackBone; 2];
  public native let fallbackAnimset: ResourceRef; // rRef<animAnimSet>
  public native let fallbackAnimationName: CName;
  public native let fallbackAnimTime: Float;
}
