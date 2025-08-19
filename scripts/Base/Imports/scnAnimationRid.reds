public native struct scnAnimationRid {
  public native let tag: scnRidTag;
  public native let animation: ref<animAnimation>;
  public native let events: ref<animEventsContainer>;
  public native let motionExtracted: Bool;
  public native let offset: Transform;
  public native let bonesCount: Uint32;
  public native let trajectoryBoneIndex: Int32;
}
