public native struct gameActionAnimationState {
  public native let replicationId: Uint32;
  public native let type: Uint16;
  public native let startTimeStamp: netTime;
  public native let stopTimeStamp: netTime;
  public native let updateBucket: Uint8;
  public native let animFeatureName: CName;
  public native let animFeature: ref<AnimFeature_AIAction>;
  public native let useRootMotion: Bool;
  public native let usePoseMatching: Bool;
  public native let motionDynamicObjectsCheck: Bool;
  public native let slideParams: ActionAnimationSlideParams;
  public native let targetObject: wref<GameObject>;
  public native let sendLoopEvent: Bool;
}
