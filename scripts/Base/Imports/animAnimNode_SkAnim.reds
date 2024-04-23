public native class animAnimNode_SkAnim extends animAnimNode_Base {
  native let animation: CName;
  native let applyMotion: Bool;
  native let isLooped: Bool;
  native let resume: Bool;
  native let collectEvents: Bool;
  native let fireAnimLoopEvent: Bool;
  native let animLoopEventName: CName;
  native let clipFront: Float;
  native let clipEnd: Float;
  native let clipFrontByEvent: CName;
  native let clipEndByEvent: CName;
  native let pushDataByTag: CName;
  native let popDataByTag: CName;
  native let pushSafeCutTag: CName;
  native let convertToAdditive: Bool;
  native let motionProvider: ref<animIMotionTableProvider>;
  native let applyInertializationOnAnimSetSwap: Bool;
}
