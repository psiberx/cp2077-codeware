public native class animAnimNode_SkAnim extends animAnimNode_Base {
  public native let animation: CName;
  public native let applyMotion: Bool;
  public native let isLooped: Bool;
  public native let resume: Bool;
  public native let collectEvents: Bool;
  public native let fireAnimLoopEvent: Bool;
  public native let animLoopEventName: CName;
  public native let clipFront: Float;
  public native let clipEnd: Float;
  public native let clipFrontByEvent: CName;
  public native let clipEndByEvent: CName;
  public native let pushDataByTag: CName;
  public native let popDataByTag: CName;
  public native let pushSafeCutTag: CName;
  public native let convertToAdditive: Bool;
  public native let motionProvider: ref<animIMotionTableProvider>;
  public native let applyInertializationOnAnimSetSwap: Bool;
}
