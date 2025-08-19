@mixedRef()
public native class audioDynamicReverbSettings extends audioAudioMetadata {
  public native let reverbType: audioDynamicReverbType;
  public native let crossover1: audioReverbCrossoverParams;
  public native let crossover2: audioReverbCrossoverParams;
  public native let maxDistance: Float;
  public native let smallReverb: CName;
  public native let smallReverbMaxDistance: Float;
  public native let smallReverbFadeOutThreshold: Float;
  public native let mediumReverb: CName;
  public native let largeReverb: CName;
  public native let vehicleReverb: CName;
  public native let overrideWeaponTail: Bool;
  public native let sourceBasedReverbSet: CName;
  public native let weaponTailType: audioWeaponTailEnvironment;
  public native let echoPositionType: audioEchoPositionType;
  public native let reportPositionType: audioEchoPositionType;
}
