public native struct scnAnimationRid {
  native let tag: scnRidTag;
  native let animation: ref<animAnimation>;
  native let events: ref<animEventsContainer>;
  native let motionExtracted: Bool;
  native let offset: Transform;
  native let bonesCount: Uint32;
  native let trajectoryBoneIndex: Int32;
}
