@mixedRef()
public native class audioBreathingTemporaryStateMetadata extends audioAudioMetadata {
  public native let inhaleSound: CName;
  public native let exhaleSound: CName;
  public native let paramChangeSpeed: Float;
  public native let targetBpm: Float;
  public native let targetTimeDistortion: Float;
  public native let time: Float;
  public native let exhaustionChangeSpeed: Float;
  public native let targetExhaustion: Float;
  public native let loopBehavior: audiobreathingLoopBehavior;
  public native let startStateFromBreath: Bool;
}
