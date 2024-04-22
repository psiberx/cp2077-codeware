public native class audioDynamicReverbSettings extends audioAudioMetadata {
  native let reverbType: audioDynamicReverbType;
  native let crossover1: audioReverbCrossoverParams;
  native let crossover2: audioReverbCrossoverParams;
  native let maxDistance: Float;
  native let smallReverb: CName;
  native let smallReverbMaxDistance: Float;
  native let smallReverbFadeOutThreshold: Float;
  native let mediumReverb: CName;
  native let largeReverb: CName;
  native let vehicleReverb: CName;
  native let overrideWeaponTail: Bool;
  native let sourceBasedReverbSet: CName;
  native let weaponTailType: audioWeaponTailEnvironment;
  native let echoPositionType: audioEchoPositionType;
  native let reportPositionType: audioEchoPositionType;
}
