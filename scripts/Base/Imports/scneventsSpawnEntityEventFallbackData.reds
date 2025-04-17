public native struct scneventsSpawnEntityEventFallbackData {
  native let owner: scnPerformerId;
  native let fallbackCachedBones: [scneventsSpawnEntityEventCachedFallbackBone; 2];
  native let fallbackAnimset: ResourceRef; // rRef<animAnimSet>
  native let fallbackAnimationName: CName;
  native let fallbackAnimTime: Float;
}
