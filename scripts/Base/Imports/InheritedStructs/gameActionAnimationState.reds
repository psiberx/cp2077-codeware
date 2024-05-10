public native struct gameActionAnimationState {
  native let replicationId: Uint32;
  native let type: Uint16;
  native let startTimeStamp: netTime;
  native let stopTimeStamp: netTime;
  native let updateBucket: Uint8;
  native let animFeatureName: CName;
  native let animFeature: ref<AnimFeature_AIAction>;
  native let useRootMotion: Bool;
  native let usePoseMatching: Bool;
  native let motionDynamicObjectsCheck: Bool;
  native let slideParams: ActionAnimationSlideParams;
  native let targetObject: wref<GameObject>;
  native let sendLoopEvent: Bool;
}
