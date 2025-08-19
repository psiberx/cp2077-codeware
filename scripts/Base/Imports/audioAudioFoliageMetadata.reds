@mixedRef()
public native class audioAudioFoliageMetadata extends audioAudioMetadata {
  public native let loopStartEvent: CName;
  public native let loopStopEvent: CName;
  public native let locomotionTotalVelocityParam: CName;
  public native let locomotionTotalVelocityThreshold: Float;
  public native let locomotionAngularVelocityMultiplier: Float;
  public native let minFoliageMeshVolumeThreshold: Float;
  public native let maxFoliageMeshHeight: Float;
  public native let playerInsideRequiredPercentage: Float;
  public native let foliageMaterials: ref<audioAudioFoliageMaterialDictionary>;
}
