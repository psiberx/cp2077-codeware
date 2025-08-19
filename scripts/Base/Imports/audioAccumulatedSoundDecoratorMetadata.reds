@mixedRef()
public native class audioAccumulatedSoundDecoratorMetadata extends audioEmitterMetadata {
  public native let accumulatedSounds: array<CName>;
  public native let inSpammingMode: Bool;
  public native let fadeParam: CName;
  public native let soundTimeout: Float;
  public native let loopStart: CName;
  public native let loopEnd: CName;
  public native let spammingSound: CName;
  public native let spammingSoundInterval: Float;
}
