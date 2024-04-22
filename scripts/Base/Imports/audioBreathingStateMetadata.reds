public native class audioBreathingStateMetadata extends audioAudioMetadata {
  native let inhaleSound: CName;
  native let exhaleSound: CName;
  native let paramChangeSpeed: Float;
  native let targetBpm: Float;
  native let targetTimeDistortion: Float;
  native let stateMinimalTime: Float;
  native let exhaustionChangeSpeed: Float;
  native let targetExhaustion: Float;
  native let loopBehavior: audiobreathingLoopBehavior;
  native let startStateFromBreath: Bool;
}
