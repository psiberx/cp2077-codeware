@mixedRef()
public native class audioFoleyLoopMappingMetadata extends audioAudioMetadata {
  public native let loopsPerAppearance: array<audioAppearanceToFoleyLoopMetadata>;
  public native let loopsPerVisualTag: array<audioVisualTagToFoleyLoopMetadata>;
}
